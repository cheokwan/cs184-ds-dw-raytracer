#include "algebra3.h"
#include "bmp/easyBMP.h"
#include "Primitive.h"

#ifndef _Sphere_h_
#define _Sphere_h_

class Sphere : public Primitive
{
private:
	vec4 center;
	double radius;

public:
	void setRadius(float newRadius);
	void setCenter(vec4 newCenter);
	virtual bool intersect(vec4 p0, vec4 p1, double *t, double maxDistance);
	virtual vec4 getNormal(vec4 point);
	Sphere();
	~Sphere();
};

#endif