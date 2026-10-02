#include "mujoco/mujoco.h"
#include "stdio.h"

char error[1000];
mjModel* m;
mjData* d;

int main(void) {
  // load model from file and check for errors
  m = mj_loadXML("models/hello.xml", NULL, error, 1000);
  if (!m) {
    printf("%s\n", error);
    return 1;
  }

  // make data corresponding to model
  d = mj_makeData(m);

  // run simulation for 10 seconds
  while (d->time < 10){
    mj_step(m, d);
    printf("Simulation time: %.3f s\n",d->time);
  }

  // free model and data
  mj_deleteData(d);
  mj_deleteModel(m);

  return 0;
}
