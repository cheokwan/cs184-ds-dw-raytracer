#include "Triangle.h"
#include <math.h>

#define EPSILON 0.0001

void Triangle::setVertex(vec3 newVertexA, vec3 newVertexB, vec3 newVertexC){
	vertexA = newVertexA;
	vertexB = newVertexB;
	vertexC = newVertexC;
	return;
}

void Triangle::setNormal(vec3 newNormalA, vec3 newNormalB, vec3 newNormalC){
	normalA = newNormalA;
	normalB = newNormalB;
	normalC = newNormalC;
	return;
}

bool Triangle::intersect(vec3 p0, vec3 p1, double *t, double maxDistance){
	//vec3 normal = ((vertexC - vertexA) ^ (vertexB - vertexA)).normalize();
	vec3 normal = (vertexC - vertexA) ^ (vertexB - vertexA);
	double denom = (p1*normal);
	double numer = (vertexA*normal)-(p0*normal);
	if ((denom < EPSILON && denom > -EPSILON) || numer/denom > maxDistance || numer/denom < 0){
		return false;
	} else {
		*t = numer/denom;
		vec3 q = (p1 * (*t)) + p0;
		double a = ((vertexC-vertexA)^(q-vertexA))*normal;
		double b = ((q-vertexA)^(vertexB-vertexA))*normal;

		if (sqrt(normal.length2()) != 0) {
			a /= normal.length2(); 
			b /= normal.length2();
		} 
		/*
		if (q[0]>-2 && q[0]<2 && q[1]>-2 && q[1]<2){
			printf("q=[%.2f %.2f %.2f]  normal=[%.2f %.2f %.2f]  a=%.2f  b=%.2f  normal=%.2f\n", q[0], q[1], q[2], normal[0], normal[1], normal[2], a, b, normal.length2());
			printf("v1=[%.2f %.2f %.2f]  v2=[%.2f %.2f %.2f]  v3=[%.2f %.2f %.2f]\n", vertexA[0], vertexA[1], vertexA[2], vertexB[0], vertexB[1], vertexB[2], vertexC[0], vertexC[1], vertexC[2]);
		}
		*/
		if (a>-EPSILON && b>-EPSILON && a+b<1){
			//printf("q=[%.2f %.2f %.2f]  normal=[%.2f %.2f %.2f]  a=%.2f  b=%.2f\n", q[0], q[1], q[2], normal[0], normal[1], normal[2], a, b);
			return true;
		}
		return false;
	}
}

vec3 Triangle::getNormal(vec3 point){
	vec3 a, b, normal;
	double r, s, t;

	a = vertexC - vertexA;
	b = vertexB - vertexA;
	normal = a^b;

	if (!interpolateNormal){
		return normal.normalize();
	} else {
		s = ((vertexC-vertexA)^(point-vertexA))*normal;
		t = ((point-vertexA)^(vertexB-vertexA))*normal;

		if (sqrt(normal.length2()) != 0) {
			s /= normal.length2(); 
			t /= normal.length2();
		}

		r = 1-s-t;

		normal = vec3((r * vertexA[0] + s * vertexB[0] + t * vertexC[0]),
							(r * vertexA[1] + s * vertexB[1] + t * vertexC[1]),
							(r * vertexA[2] + s * vertexB[2] + t * vertexC[2]));

		return normal.normalize();
	}
}

Triangle::Triangle(){
	vertexA = vec3(-2, 2, 8);
	vertexB = vec3(-2, -2, 8);
	vertexC = vec3(2, -2, 8);
	interpolateNormal = false;
}

Triangle::Triangle(vec3 newNormalA, vec3 newNormalB, vec3 newNormalC){
	interpolateNormal = true;
	normalA = newNormalA;
	normalB = newNormalB;
	normalC = newNormalC;
}

Triangle::~Triangle(){
}
