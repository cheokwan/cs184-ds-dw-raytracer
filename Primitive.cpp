#include "Primitive.h"

void Primitive::setMatrix(mat4 m){
	objToWorld = m;
	worldToObj = m;
}
