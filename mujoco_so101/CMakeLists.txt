cmake_minimum_required(VERSION 3.16)

project(mujoco_so101)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(mujoco REQUIRED)
find_package(Threads REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(so101_sim_robot_gui
    src/main_robot_gui.cpp
)

add_executable(so101_sim
    src/main.cpp
)

add_executable(so101_sim_render
    src/main_render.cpp
)

add_executable(so101_sim_robot
    src/main_robot.cpp
)

target_link_libraries(so101_sim
    PRIVATE
    mujoco::mujoco
)

target_link_libraries(so101_sim_render
    PRIVATE
    mujoco::mujoco
    glfw
)

target_link_libraries(so101_sim_robot
    PRIVATE
    mujoco::mujoco
    glfw
)

#for full gui implementation
set(MUJOCO_SIMULATE_LIBRARY
    "$ENV{HOME}/mujoco/build/lib/libsimulate.a"
)

target_link_libraries(so101_sim_robot_gui
    PRIVATE
    mujoco::mujoco
    ${MUJOCO_SIMULATE_LIBRARY}
    "/home/luis/mujoco/build/lib/libglfw3.a"
    Threads::Threads
)


