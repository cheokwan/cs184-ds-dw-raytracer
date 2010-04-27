#ifndef CAMERA_H
#define CAMERA_H

#include "algebra3.h"

class Camera {
  vec3 look_from;
  vec3 look_at;
  vec3 up;
  float field_of_view;
  float aspect_ratio;
  float z_near;
  float z_far;

  vec3 look_dir;
  vec3 right;
  float screen_x;
  float screen_y;

 public:
  Camera();
  Camera(vec3 look_from, vec3 look_at, vec3 up,
         float field_of_view, float aspect_ratio,
         float z_near, float z_far);
  ~Camera();
  void generateRay(vec2 sample, vec4& ray_ori, vec4& ray_dir);
  vec4 position();
  void debugmsg();
};

#endif
