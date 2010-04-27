#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>

void matprint(mat4 mat) {
  for (int i = 0; i < 4; i++) {
    printf("| %.2f  %.2f  %.2f  %.2f |\n", mat[i][0], mat[i][1], mat[i][2], mat[i][3]);
  }
}

void vecprint(vec3 vec) {
  printf("< %.2f, %.2f, %.2f >", vec[0], vec[1], vec[2]);
}

void vecprint(vec4 vec) {
  printf("< %.2f, %.2f, %.2f, %.2f >", vec[0], vec[1], vec[2], vec[3]);
}


#endif
