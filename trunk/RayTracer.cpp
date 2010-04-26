#include "RayTracer.h"


Raytracer::Raytracer(){
	Sphere *s1 = new Sphere();
	s1->setRadius(1);
	s1->kd = Color(1, 0.1, 0.1);
	s1->ks = Color(1.0, 1.0, 1.0);
	s1->ke = Color(0, 0, 0);
	s1->sp = 10.0;
//	Triangle *t1 = new Triangle();
	
	Light *l1 = new Light(-2, -2, 3, Color(1, 1, 1), 1);
	//l1->attn = vec3(1, 0.2, 0.08);

	primitives.push_back(s1);
//	primitives.push_back(t1);
	lights.push_back(l1);
	globalAmbient = Color(0.1, 0.1, 0.1);
}

Raytracer::~Raytracer(){
}

bool Raytracer::visible(vec3 p0, Light *l){
	int i;
	vec3 p1;
	if (l->directional)
		p1 = -(l->pos);
	else 
		p1 = l->pos - p0;
	double dummy;
	double depth = p1.length();

	if (depth <= 0.00001){
		return true;
	}

	p0 = p0 + (p1.normalize() * 0.00001);
	
	for(i = 0; i < primitives.size(); i++){
		if (primitives.at(i)->intersect(p0, p1, &dummy, depth)){
			return false;
		}
	}
	return true;
}
	

void Raytracer::trace(vec3 p0, vec3 p1, double depth, Color *c){
	int i;
	double t;
	double minT = depth;
	int minPrimIndex = -1;
	double attn;
	vec3 lDirection;
	vec3 h;
	vec3 normal;

	for(i = 0; i < primitives.size(); i++){
		if (primitives.at(i)->intersect(p0, p1, &t, depth)){
			if (t < minT){
				minPrimIndex = i;
				minT = t;
			}
		}
	}

	if (minPrimIndex == -1){
		*c = Color(0,0,0);
	} else {
		*c = globalAmbient + primitives.at(minPrimIndex)->ke;
		for (i = 0; i < lights.size(); i++){
			attn = 1.0/((lights.at(i)->attn)[0] + (lights.at(i)->attn)[1] * minT + (lights.at(i)->attn)[2] * minT * minT);
			if (visible(p0 + (minT*p1), lights.at(i))){
				h = (-(p0 + (minT * p1)) + (lights.at(i)->pos - (p0 + (minT * p1)))).normalize();
				if (lights.at(i)->directional)
					lDirection = vec3(lights.at(i)->pos);
				else
					lDirection = p0 + (minT*p1) - vec3(lights.at(i)->pos);
				normal =  primitives.at(minPrimIndex)->getNormal(p0 + (minT*p1));
				lDirection = -lDirection;
				*c = *c + ((attn * lights.at(i)->color) * ((primitives.at(minPrimIndex)->kd * MAX(lDirection * normal, 0))
					+ (primitives.at(minPrimIndex)->ks * pow((normal * h), primitives.at(minPrimIndex)->sp))));

			} else {
				
			}
		}
	}
}
