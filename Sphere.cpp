#include "Sphere.h"

void Sphere::setRadius(float newRadius){
	radius = newRadius;
	return;
}

void Sphere::setCenter(vec3 newCenter){
	center = vec3(newCenter);
	return;
}

int Sphere::intersect(vec3 p0, vec3 p1){
	double a, b, c, d;
	a = p1 * p1;
	b = 2 * ( p1 * (p0 - center) );
	c = (p0 - center) * (p0 - center) - (radius * radius);

	d = (b * b) - ( 4 * a * c);

	//printf ("Radius: %.2f, Center: %.2f %.2f %.2f, Discriminant: %.2f\nA: %.2f, B: %.2f, C: %.2f, P0: %.2f %.2f %.2f, P1: %.2f %.2f %.2f\n", radius, center[0], center[1], center[2], d, a, b, c, p0[0], p0[1], p0[2], p1[0], p1[1], p1[2]);
	if (d < 0){
		return 0;
	}
	return 1;
}

Sphere::Sphere(){
	center = vec3(0, 0, 6);
	radius = 3;
}

Sphere::~Sphere(){
}