#include "Sphere.h"
#include <math.h>

void Sphere::setRadius(float newRadius){
	radius = newRadius;
	return;
}

void Sphere::setCenter(vec4 newCenter){
	center = vec4(newCenter);
	return;
}

bool Sphere::intersect(vec4 p0, vec4 p1, double *t, double maxDistance){
	double a, b, c, d, s1, s2;

	a = p1 * p1;
	b = 2 * ( p1 * (p0 - center) );
	c = (p0 - center) * (p0 - center) - (radius * radius);

	d = (b * b) - ( 4 * a * c);

	//printf ("Radius: %.2f, Center: %.2f %.2f %.2f, Discriminant: %.2f\nA: %.2f, B: %.2f, C: %.2f, P0: %.2f %.2f %.2f, P1: %.2f %.2f %.2f\n", radius, center[0], center[1], center[2], d, a, b, c, p0[0], p0[1], p0[2], p1[0], p1[1], p1[2]);
	if (d < 0.000001){
		return false;
	} else if (d <= 0.0000001 && d >= -0.0000001) {
		s1 = -b/(2*a);
		*t = s1;
	} else {
		s1 = (-b + sqrt(d))/(2*a);
		s2 = (-b - sqrt(d))/(2*a);
		if (s1 < 0.0000001 && s2 < 0.0000001){
			return false;
		} else if (s1 < 0.0000001){
			*t = s2;
		} else if (s2 < 0.0000001){
			*t = s1;
		} else if (s1 < s2){
			*t = s1;
		} else {
			*t = s2;
		}
	}
	if (*t > maxDistance){
		return false;
	}
	return true;
}

vec4 Sphere::getNormal(vec4 point){
	return (point-center).normalize();
}

Sphere::Sphere(){
	center = vec4(0, 0, 6, 1);
	radius = 3;
}

Sphere::Sphere(double x, double y, double z, double r, mat4 t){
	center = vec4(x, y, z, 1);
	radius = r;
	setMatrix(t);
}

Sphere::~Sphere(){
}