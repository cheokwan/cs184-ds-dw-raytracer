#include "algebra3.h"
#include "bmp/easyBMP.h"
#include "Primitive.h"

#ifndef _Sphere_h_
#define _Sphere_h_

class Sphere : public Primitive
{
private:
	vec3 center;
	double radius;

public:
	void setRadius(float newRadius);
	void setCenter(vec3 newCenter);
	virtual bool intersect(vec3 p0, vec3 p1, double *t, double maxDistance);
	virtual vec3 getNormal(vec3 point);
	Sphere();
	~Sphere();
};

#endif