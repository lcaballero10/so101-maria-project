cmake_minimum_required(VERSION 3.16)

project(mujoco_so101)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(mujoco REQUIRED)

add_executable(so101_sim
    src/main.cpp
)

add_executable(so101_sim_render
    src/main_render.cpp
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
