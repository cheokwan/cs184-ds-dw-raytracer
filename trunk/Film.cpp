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
    Color accum_color(0.0, 0.0, 0.0);
    for (int s = 0; s < depth; s++) {
      accum_color = accum_color + color_buffer[p*depth+s];
    }
    image->SetPixel(p % width, p / width, accum_color.toRGBA());
  }
  return image;
}
