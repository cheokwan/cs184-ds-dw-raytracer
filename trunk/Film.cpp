#include "Film.h"
#include "string.h"

Film::Film() {
}

Film::Film(int width, int height, int depth) {
  this->width = width;
  this->height = height;
  this->depth = depth;
  total_samples = width * height * depth;
  color_buffer = new Color[total_samples];
  current_sample = 0;
  image = new BMP();
  image->SetSize(width, height);
}

Film::~Film() {
  delete[] color_buffer;
  delete image;
}

bool Film::commit(Color color) {
  if (current_sample >= total_samples) {
    return false;
  }
  color_buffer[current_sample++] = color;
  return true;
}

BMP* Film::generateImage() {
  int total_pixels = width * height;
  for (int p = 0; p < total_pixels; p++) {
    float accum_r = 0.0, accum_g = 0.0, accum_b = 0.0;
    for (int s = 0; s < depth; s++) {
      accum_r += color_buffer[p*depth+s].r;
      accum_g += color_buffer[p*depth+s].g;
      accum_b += color_buffer[p*depth+s].b;
    }
    Color color(accum_r/depth, accum_g/depth, accum_b/depth);
    image->SetPixel(p % width, p / width, color.toRGBA());
  }
  return image;
}
