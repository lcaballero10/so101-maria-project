
#include <mujoco/mujoco.h>

#include "simulate/simulate.h"
#include "simulate/glfw_adapter.h"

#include <chrono>
#include <cstdio>
#include <memory>
#include <mutex>
#include <thread>

// MuJoCo model and data
mjModel* m = nullptr;
mjData* d = nullptr;

char error[1000];

// Physics loop: executed in a separate thread
void physicsLoop(mujoco::Simulate* sim) {

    while (!sim->exitrequest.load()) {

        {
            // Protect simulation data shared with the GUI
            const std::unique_lock<std::recursive_mutex> lock(sim->mtx);

            if (sim->run) {
                // Advance the simulation
                mj_step(m, d);
            } else {
                // Update positions while paused
                mj_forward(m, d);
            }
        }

        // Avoid running the loop as fast as possible
        std::this_thread::sleep_for(
            std::chrono::milliseconds(1)
        );
    }
}

int main() {

    // ---------------------------------------
    // Load SO-101 model
    // ---------------------------------------

    m = mj_loadXML("models/scene.xml", nullptr, error, sizeof(error));

    if (!m) {
        std::printf("Error loading model: %s\n", error);
        return 1;
    }

    d = mj_makeData(m);

    if (!d) {
        std::printf("Could not allocate simulation data\n");
        mj_deleteModel(m);
        return 1;
    }

    // ---------------------------------------
    // Initialize GUI visualization objects
    // ---------------------------------------

    mjvCamera cam;
    mjvOption opt;
    mjvPerturb pert;

    mjv_defaultCamera(&cam);
    mjv_defaultOption(&opt);
    mjv_defaultPerturb(&pert);

    // ---------------------------------------
    // Create the official MuJoCo GUI
    // ---------------------------------------

    auto sim = std::make_unique<mujoco::Simulate>(
        std::make_unique<mujoco::GlfwAdapter>(),
        &cam,
        &opt,
        &pert,
        false
    );

    // Register our model and data with the GUI
    sim->Load(m, d, "models/scene.xml");

    // ---------------------------------------
    // Start the physics thread
    // ---------------------------------------

    std::thread physicsThread(physicsLoop, sim.get());

    // ---------------------------------------
    // Start the GUI (main thread)
    // ---------------------------------------

    sim->RenderLoop();

    // Wait for physics thread to finish
    physicsThread.join();

    // ---------------------------------------
    // Clean up
    // ---------------------------------------

    sim.reset();

    mj_deleteData(d);
    mj_deleteModel(m);

    return 0;
}
