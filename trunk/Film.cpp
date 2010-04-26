#include "Film.h"
#include "string.h"

Film::Film() {
}

Film::Film(int width, int height, int depth) {
  this->width = width;
  this->height = height;
  this->depth = depth;
  total_samples = width * height * depth;
  color_buffer = new char[total_samples];
  memset(color_buffer, 0xFF, total_samples);
  current_sample = 0;
}

Film::~Film() {
  delete[] color_buffer;
}

bool Film::commit(char color) {
  if (current_sample >= total_samples) {
    return false;
  }
  color_buffer[current_sample++] = color;
  return true;
}
