#include "algebra3.h"

#ifndef _Sphere_h_
#define _Sphere_h_

class Sphere
{
private:
	vec3 center;
	float radius;
	float ka[3];
	float kd[3];
	float ks[3];
	float kr[3];
	float sp;

public:
	void setRadius(float newRadius);
	void setCenter(vec3 newCenter);
	int intersect(vec3 p0, vec3 p1);
	Sphere();
	~Sphere();
};

#endif