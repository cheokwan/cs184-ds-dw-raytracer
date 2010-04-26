#include "algebra3.h"
#include "Color.h"
#include "Light.h"
#include "Primitive.h"
#include "Sphere.h"
#include "Triangle.h"
#include <math.h>
#include <vector>
using namespace std;

#ifndef _Raytracer_h_
#define _Raytracer_h_

class Raytracer
{
public:
	vector<Primitive*> primitives;
	vector<Light*> lights;
	Color globalAmbient;
	void trace(int reflects, vec4 p0, vec4 p1, double depth, Color *color);
	bool visible(vec4 p, Light *l);
	Raytracer();
	~Raytracer();
};

#endif