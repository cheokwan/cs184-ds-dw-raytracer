#include "Color.h"

#ifndef _Primitive_h_
#define _Primitive_h_

class Primitive
{
public:
	virtual bool intersect(vec3 p0, vec3 p1, double *t, double maxDistance) = 0;
	virtual vec3 getNormal(vec3 point) = 0;
	Color kd;
	Color ks;
	Color ke;
	double sp;
};

#endif