#ifndef FILM_H
#define FILM_H

class Film {
  int width;
  int height;
  int depth;
  char* color_buffer;
  int total_samples;
  int current_sample;

 public:
  Film();
  Film(int width, int height, int depth);
  ~Film();
  /*  commit is performed in order only.
      pixels are swept horizontally from upper left corner to lower right
      corner, same order as the Sampler generates samples.   */
  bool commit(char color);
};

#endif
