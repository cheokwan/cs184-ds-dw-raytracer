#include "Primitive.h"

void Primitive::setMatrix(mat4 m){
	objToWorld = m;
	worldToObj = m.inverse();
}

void Primitive::setMaterial(Color diffuse, Color specular, Color emission, Color reflection, Color ambient, double shininess) {
  kd = diffuse;
  ks = specular;
  ke = emission;
  kr = reflection;
  ka = ambient;
  sp = shininess;
}
