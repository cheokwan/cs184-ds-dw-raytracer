#include "Triangle.h"
#include <math.h>

#define EPSILON 0.0001

void Triangle::setVertex(vec4 newVertexA, vec4 newVertexB, vec4 newVertexC){
	vertexA = newVertexA;
	vertexB = newVertexB;
	vertexC = newVertexC;
	return;
}

void Triangle::setNormal(vec4 newNormalA, vec4 newNormalB, vec4 newNormalC){
	normalA = newNormalA;
	normalB = newNormalB;
	normalC = newNormalC;
	return;
}

bool Triangle::intersect(vec4 p0, vec4 p1, double *t, double maxDistance){
	//vec4 normal = ((vertexC - vertexA) ^ (vertexB - vertexA)).normalize();
	p0[3] = 1;
	p1[3] = 0;
	vec3 sp0 = vec3(p0, 3);
	vec3 sp1 = vec3(p1, 3);
	vec3 snorm;
	vec4 q;

	snorm = ((vec3(vertexC, 3) - vec3(vertexA, 3)) ^ (vec3(vertexB, 3) - vec3(vertexA, 3)));
	//vec4 normal = vec4((vec3(vertexC) - vec3(vertexA)) ^ (vec3(vertexB) - vec3(vertexA)));
	vec4 normal = vec4(snorm);
	normal[3] = 0;
	double denom;
	denom = sp1*snorm;
	double numer;
	numer = (vec3(vertexA, 3)*snorm)-(sp0*snorm);



	if ((denom < EPSILON && denom > -EPSILON) || numer/denom > maxDistance || numer/denom < 0){
		return false;
	} else {
		*t = numer/denom;
		if (*t < 0.00001)
			return false;
		q = p1 * (*t) + p0;
		double a = (vec3(vertexC-vertexA, 3)^vec3(q-vertexA, 3))*snorm;
		double b = (vec3(q-vertexA, 3)^vec3(vertexB-vertexA, 3))*snorm;

		if (sqrt(snorm.length2()) != 0) {
			a /= snorm.length2(); 
			b /= snorm.length2();
		} 
		
	//	if (q[0]>-2 && q[0]<2 && q[1]>-2 && q[1]<2){
	/*	if (*t > 0.00001){
			printf("sp1=[%.2f %.2f %.2f]  t=%.2f  denom=%.2f  numer=%.2f\n", sp1[0], sp1[1], sp1[2], t, denom, numer);
			printf("q=[%.2f %.2f %.2f]  normal=[%.2f %.2f %.2f]  a=%.2f  b=%.2f  normal=%.2f\n", q[0], q[1], q[2], snorm[0], snorm[1], snorm[2], a, b, normal.length2());
			printf("v1=[%.2f %.2f %.2f]  v2=[%.2f %.2f %.2f]  v3=[%.2f %.2f %.2f]\n", vertexA[0], vertexA[1], vertexA[2], vertexB[0], vertexB[1], vertexB[2], vertexC[0], vertexC[1], vertexC[2]);


	//	}*/
		
		if (a>-EPSILON && b>-EPSILON && a+b<1){
			//printf("q=[%.2f %.2f %.2f]  normal=[%.2f %.2f %.2f]  a=%.2f  b=%.2f\n", q[0], q[1], q[2], normal[0], normal[1], normal[2], a, b);
			return true;
		}
		return false;
	}
}

vec4 Triangle::getNormal(vec4 point){
	vec4 a, b, normal;
	double r, s, t;

	a = vertexC - vertexA;
	b = vertexB - vertexA;
	normal = vec4(vec3(a, 3)^vec3(b, 3));
	normal[3] = 0;

	if (!interpolateNormal){
		return normal.normalize();
	} else {
		s = (vec3(vertexC-vertexA, 3)^vec3(point-vertexA, 3))*vec3(normal, 3);
		t = (vec3(point-vertexA, 3)^vec3(vertexB-vertexA,3))*vec3(normal, 3);

		if (sqrt(normal.length2()) != 0) {
			s /= normal.length2(); 
			t /= normal.length2();
		}

		r = 1-s-t;

		normal = vec4((r * vertexA[0] + s * vertexB[0] + t * vertexC[0]),
							(r * vertexA[1] + s * vertexB[1] + t * vertexC[1]),
							(r * vertexA[2] + s * vertexB[2] + t * vertexC[2]), 0);

		return normal.normalize();
	}
}

Triangle::Triangle(){
	vertexA = vec4(2, 2, 5.5, 1);
	vertexB = vec4(-2, 2, 7.5, 1);
	vertexC = vec4(0, -1.5, 6.5, 1);
	interpolateNormal = false;
}

Triangle::Triangle(vec4 newVertexA, vec4 newVertexB, vec4 newVertexC, vec4 newNormalA, vec4 newNormalB, vec4 newNormalC, mat4 t){
	interpolateNormal = true;

	vertexA = newVertexA;
	vertexB = newVertexB;
	vertexC = newVertexC;

	normalA = newNormalA;
	normalB = newNormalB;
	normalC = newNormalC;

	setMatrix(t);
}

Triangle::Triangle(vec4 newVertexA, vec4 newVertexB, vec4 newVertexC, mat4 t){
	interpolateNormal = false;

	vertexA = newVertexA;
	vertexB = newVertexB;
	vertexC = newVertexC;

	setMatrix(t);
}

Triangle::~Triangle(){
}
