#include "algebra3.h"
#include "Sampler.h"
#include "Camera.h"

#include <stdio.h>
/*  Dedicated to running the milestone  */
void milestone() {
  int size_x = 160;
  int size_y = 120;
  vec3 cam_lookfrom(0.0, 0.0, -5.0);
  vec3 cam_lookat(0.0, 0.0, 1.0);
  vec3 cam_up(0.0, 1.0, 0.0);
  float fov = 60.0;

  Sampler test_sampler(3, 3, 2);
  vec2 sample;
  int i = 0;
  while (test_sampler.getSample(sample)) {
    printf("sample x: %.2f,  y: %.2f\n", sample[0], sample[1]);
  }

}

int main(int argc, char** argv) {
  milestone();
}
