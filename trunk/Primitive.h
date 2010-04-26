#include "Color.h"

#ifndef _Primitive_h_
#define _Primitive_h_

class Primitive
{
public:
	virtual bool intersect(vec4 p0, vec4 p1, double *t, double maxDistance) = 0;
	virtual vec4 getNormal(vec4 point) = 0;
	Color kd;
	Color ks;
	Color ke;
	Color kr;
	double sp;
};

#endif