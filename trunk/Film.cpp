#include "Film.h"

Film::Film() {
}

Film::Film(int width, int height, int depth) {
  this->width = width;
  this->height = height;
  this->depth = depth;
  colorbuffer = new char[width*height*depth];
}

Film::~Film() {
}

