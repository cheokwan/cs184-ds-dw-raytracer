#include "Camera.h"
#include <math.h>

Camera::Camera(vec3 look_from, vec3 look_at, vec3 up,
               float field_of_view, float aspect_ratio,
               float z_near, float z_far) {
  this->look_from = look_from;
  this->look_at = look_at;
  this->up = up;
  this->field_of_view = field_of_view;
  this->aspect_ratio = aspect_ratio;
  this->z_near = z_near;
  this->z_far = z_far;

  look_dir = (look_at - look_from).normalize();
  right = (look_dir ^ up).normalize();
  up = (right ^ look_dir).normalize();
  screen_x = aspect_ratio * tan(field_of_view) * z_near;
  screen_y = tan(field_of_view) * z_near;
}

Camera::~Camera() {
}

void Camera::generateRay(vec2 sample, vec3& ray) {
  ray = (z_near * look_dir) +
        (screen_x * sample[0] * right) +
        (screen_y * sample[1] * up);
}

vec3 Camera::position() {
  return look_from;
}
