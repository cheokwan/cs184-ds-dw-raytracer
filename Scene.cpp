#include "algebra3.h"
#include "Sampler.h"
#include "Camera.h"

#include "bmp/EasyBMP.h"
#include "Sphere.h"

#include <stdio.h>
/*  Dedicated to running the milestone  */
void milestone() {
  int size_x = 800;
  int size_y = 600;
  vec3 cam_lookfrom(0.0, 0.0, 4.0);
  vec3 cam_lookat(1.0, 0.0, -1.0);
  vec3 cam_up(0.0, 1.0, 0.0);
  float fov = 60.0;


  Sphere sphere = Sphere();
  sphere.setRadius(2.0);
  sphere.setCenter(vec3(0.0, 0.0, -16.0));

  RGBApixel *red, *black;
  red = (RGBApixel*) malloc (sizeof(RGBApixel));
  red->Red = 255; red->Blue = 0; red->Green = 0; red->Alpha = 0;
  black = (RGBApixel*) malloc (sizeof(RGBApixel));
  black->Red = 0; black->Blue = 0; black->Green = 0; black->Alpha = 0;
  BMP *myPic = new BMP();
  myPic->SetSize(size_x, size_y);
  int x = 0; int y = 0;


  Sampler test_sampler(size_x, size_y, 1);
  Camera camera(cam_lookfrom, cam_lookat, cam_up, fov, size_x / float(size_y), 1.0, 10.0);
  vec2 sample;
  vec3 ray;
  while (test_sampler.getSample(sample)) {
    //printf("sample x: %.2f,  y: %.2f\n", sample[0], sample[1]);
    camera.generateRay(sample, ray);
    //printf("ray (%.2f, %.2f, %.2f)\n", ray[0], ray[1], ray[2]);

    if (x == size_x) {
      y++;
      x = 0;
    }
    if (sphere.intersect(camera.position(), ray)) {
      myPic->SetPixel(x, y, *red);
    }
    else {
      myPic->SetPixel(x, y, *black);
    }
    x++;
  }

  myPic->WriteToFile("milestone.bmp");
  delete myPic;
  free(red);
  free(black);
}

int main(int argc, char** argv) {
  milestone();
}
