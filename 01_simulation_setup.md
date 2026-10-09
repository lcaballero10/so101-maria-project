# Simulation Environment Setup

For the setup of the simulation environment we followed [1].

MuJoCo was installed by source following [2].

Create a folder for the MuJoCo project.
```bash
mkdir mujoco_so101
cd mujoco_so101
mkdir src #for cpp files
mkdir models #for .xml files
mkdir CMakeLists.txt #configuration file as we use cpp
```

We create an example file within models folder
```bash
# In mujoco_so101 directory
cd models
touch hello.xml
```
Insert the following code in ```hello.xml```
```xml
<mujoco>
  <worldbody>
    <light diffuse=".5 .5 .5" pos="0 0 3" dir="0 0 -1"/>
    <geom type="plane" size="1 1 0.1" rgba=".9 0 0 1"/>
    <body pos="0 0 1">
      <joint type="free"/>
      <geom type="box" size=".1 .2 .3" rgba="0 .9 0 1"/>
    </body>
  </worldbody>
</mujoco>
```
Now, within the src folder create a file and insert the following code:
```bash
cd src
touch main.cpp
```
```cpp
//main.cpp content
#include "mujoco.h"
#include "stdio.h"

char error[1000];
mjModel* m;
mjData* d;

int main(void) {
  // load model from file and check for errors
  m = mj_loadXML("hello.xml", NULL, error, 1000);
  if (!m) {
    printf("%s\n", error);
    return 1;
  }

  // make data corresponding to model
  d = mj_makeData(m);

  // run simulation for 10 seconds
  while (d->time < 10)
    mj_step(m, d);

  // free model and data
  mj_deleteData(d);
  mj_deleteModel(m);

  return 0;
}
```

## References

[1] https://mujoco.readthedocs.io/en/stable/overview.html \
[2] https://mujoco.readthedocs.io/en/latest/programming/#building-from-source \