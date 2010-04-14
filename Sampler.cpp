#include "Sampler.h"

Sampler::Sampler(int pixel_x, int pixel_y, int samplings) {
  this->pixel_x = pixel_x;
  this->pixel_y = pixel_y;
  this->samplings = samplings;

  x_epsilon = 2.0 / pixel_x / double(samplings + 1);
  y_epsilon = 2.0 / pixel_y / double(samplings + 1);
  current_pixel = vec2(-1.0, 1.0); // upper left hand corner of screen.
  current_sample = vec2(current_pixel);
  current_pixel_remaining_samples = samplings * samplings;
  has_more_pixels = true;

  x_pixel_count = 0;
  y_pixel_count = 0;
}

Sampler::~Sampler() {
}

bool Sampler::getSample(vec2& sample) {
  if (current_pixel_remaining_samples == 0) {
    has_more_pixels = nextPixel(current_pixel);
    current_sample = vec2(current_pixel);
    current_pixel_remaining_samples = samplings * samplings;
  }
  if (!has_more_pixels) {
    return false;
  }
  if (current_pixel_remaining_samples % samplings == 0) {
    current_sample[0] = current_pixel[0] + x_epsilon;
    current_sample[1] = current_sample[1] - y_epsilon;
  }
  else {
    current_sample[0] = current_sample[0] + x_epsilon;
  }
  current_pixel_remaining_samples--;
  sample = vec2(current_sample);
  return true;
}


bool Sampler::nextPixel(vec2& pixel) {
  double next_x = current_pixel[0] + 2.0 / double(pixel_x);
  double next_y = current_pixel[1];
  x_pixel_count++;
  if (x_pixel_count >= pixel_x) {
    next_x = -1.0;
    next_y = current_pixel[1] - 2.0 / double(pixel_y);
    x_pixel_count = 0;
    y_pixel_count++;
  }
  if (y_pixel_count >= pixel_y) {
    return false;  // run out of pixels
  }
  pixel = vec2(next_x, next_y);
  return true;
}
