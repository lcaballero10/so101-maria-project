# Robotic Arm Setup in Simulation Environment

We create a copy of the main_render.cpp file and change the xml path. We can see the modification in this [file](mujoco_so101/src/main_robot.cpp)

However, we cannot exploit the standard GUI functionalities given by the prebuilt simulator GUI.

As a demonstration, it can be opened in bash by executing the following.

```bash
cd ~/projects/so101-maria-project/mujoco_so101/
~/mujoco/build/bin/simulate models/scene.xml
```

For teleoperation purposes, it may not be needed to execute the simulator with the standar GUI functionalities and the robot. Next step is to teleoperate the robot in simulation via the keyboard.