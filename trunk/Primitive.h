#include "Color.h"
#include "algebra3.h"

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
	Color ka;
	double sp;
	mat4 objToWorld;
	mat4 worldToObj;
	void setMatrix(mat4 m);
        void setMaterial(Color diffuse, Color specular, Color emission, Color reflective, Color ambient, double shininess);
};

#endif
