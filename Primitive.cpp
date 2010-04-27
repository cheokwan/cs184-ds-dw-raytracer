#include "Primitive.h"

void Primitive::setMatrix(mat4 m){
	objToWorld = m;
	worldToObj = m.inverse();
}

void Primitive::setMaterial(Color diffuse, Color specular, Color emission, Color reflective, Color ambient, double shininess) {
  kd = diffuse;
  ks = specular;
  ke = emission;
  kr = reflective;
  ka = ambient;
  sp = shininess;
}
