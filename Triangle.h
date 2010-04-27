#include "algebra3.h"
#include "bmp/easyBMP.h"
#include "Primitive.h"

#ifndef _Triangle_h_
#define _Triangle_h_

class Triangle : public Primitive
{
private:
	vec4 vertexA;
	vec4 vertexB;
	vec4 vertexC;
	bool interpolateNormal;
	vec4 normalA;
	vec4 normalB;
	vec4 normalC;


public:
	virtual bool intersect(vec4 p0, vec4 p1, double *t, double maxDistance);
	virtual vec4 getNormal(vec4 point);
	void setVertex(vec4 newVertexA, vec4 newVertexB, vec4 newVertexC);
	void setNormal(vec4 newNormal, vec4 newNormalB, vec4 newNormalC);
	Triangle();
	Triangle(vec4 newVertexA, vec4 newVertexB, vec4 newVertexC, vec4 newNormalA, vec4 newNormalB, vec4 newNormalC, mat4 t);
	Triangle(vec4 newVertexA, vec4 newVertexB, vec4 newVertexC, mat4 t);
	~Triangle();
};

#endif