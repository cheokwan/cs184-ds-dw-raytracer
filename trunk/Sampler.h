#ifndef SAMPLER_H
#define SAMPLER_H

#include "algebra3.h"

class Sampler {
  int pixels_x;
  int pixels_y;
  int samplings;      // each pixel will have samplings^2 samples spread
                      // uniformaly throughout the "square".
  double x_epsilon;   // offset in x within a pixel.
  double y_epsilon;   // offset in y within a pixel.
  vec2 current_pixel;
  vec2 current_sample;
  int  current_pixel_remaining_samples;
  bool has_more_pixels;

  bool nextPixel(vec2& pixel);
  int x_pixel_count;
  int y_pixel_count;

 public:
  Sampler();
  Sampler(int pixels_x, int pixels_y, int samplings);
  ~Sampler();
  bool getSample(vec2& sample);
  void debugmsg();
};

#endif
