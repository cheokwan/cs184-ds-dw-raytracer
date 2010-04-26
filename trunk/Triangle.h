#include "algebra3.h"
#include "bmp/easyBMP.h"
#include "Primitive.h"

#ifndef _Triangle_h_
#define _Triangle_h_

class Triangle : public Primitive
{
private:
	vec3 vertexA;
	vec3 vertexB;
	vec3 vertexC;
	bool interpolateNormal;
	vec3 normalA;
	vec3 normalB;
	vec3 normalC;


public:
	virtual bool intersect(vec3 p0, vec3 p1, double *t, double maxDistance);
	virtual vec3 getNormal(vec3 point);
	void setVertex(vec3 newVertexA, vec3 newVertexB, vec3 newVertexC);
	void setNormal(vec3 newNormal, vec3 newNormalB, vec3 newNormalC);
	Triangle();
	Triangle(vec3 newNormalA, vec3 newNormalB, vec3 newNormalC);
	~Triangle();
};

#endif