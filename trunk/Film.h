#ifndef FILM_H
#define FILM_H

class Film {
  char* colorbuffer;
  int width;
  int height;
  int depth;

 public:
  Film();
  Film(int width, int height, int depth);
  ~Film();
};

#endif
