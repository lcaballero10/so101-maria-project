#include "mujoco/mujoco.h"
#include "GLFW/glfw3.h"
#include "stdio.h"

char error[1000];

mjModel* m;
mjData* d;

// MuJoCo visualization objects
mjvCamera cam;
mjvOption opt;
mjvScene scn;
mjrContext con;


int main(void) {

  // --------------------------------------------------
  // load model from file and check for errors
  // --------------------------------------------------

  m = mj_loadXML("models/hello.xml", NULL, error, 1000);

  if (!m) {
    printf("%s\n", error);
    return 1;
  }


  // --------------------------------------------------
  // make data corresponding to model
  // --------------------------------------------------

  d = mj_makeData(m);


  // --------------------------------------------------
  // initialize GLFW
  // --------------------------------------------------

  if (!glfwInit()) {
    printf("Could not initialize GLFW\n");
    return 1;
  }

  GLFWwindow* window =
      glfwCreateWindow(1200, 900, "MuJoCo", NULL, NULL);

  if (!window) {
    printf("Could not create GLFW window\n");
    glfwTerminate();
    return 1;
  }

  glfwMakeContextCurrent(window);

  // V-sync
  glfwSwapInterval(1);


  // --------------------------------------------------
  // initialize MuJoCo visualization
  // --------------------------------------------------

  mjv_defaultCamera(&cam);
  mjv_defaultOption(&opt);
  mjv_defaultScene(&scn);
  mjr_defaultContext(&con);

  mjv_makeScene(m, &scn, 2000);
  mjr_makeContext(m, &con, mjFONTSCALE_150);


  // --------------------------------------------------
  // run simulation
  // --------------------------------------------------

  while (!glfwWindowShouldClose(window)) {

    // step physics
    mj_step(m, d);

    printf("Simulation time: %.3f s\n", d->time);


    // ------------------------------------------------
    // update MuJoCo scene
    // ------------------------------------------------

    mjv_updateScene(
        m,
        d,
        &opt,
        NULL,
        &cam,
        mjCAT_ALL,
        &scn
    );


    // ------------------------------------------------
    // get window size
    // ------------------------------------------------

    int width;
    int height;

    glfwGetFramebufferSize(
        window,
        &width,
        &height
    );

    mjrRect viewport = {
        0,
        0,
        width,
        height
    };


    // ------------------------------------------------
    // render scene
    // ------------------------------------------------

    mjr_render(
        viewport,
        &scn,
        &con
    );


    // display frame
    glfwSwapBuffers(window);

    // process keyboard/mouse/window events
    glfwPollEvents();
  }


  // --------------------------------------------------
  // free visualization resources
  // --------------------------------------------------

  mjr_freeContext(&con);
  mjv_freeScene(&scn);

  glfwDestroyWindow(window);
  glfwTerminate();


  // --------------------------------------------------
  // free model and data
  // --------------------------------------------------

  mj_deleteData(d);
  mj_deleteModel(m);

  return 0;
}
