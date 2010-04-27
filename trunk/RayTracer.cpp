#include "RayTracer.h"


Raytracer::Raytracer(){
}

Raytracer::~Raytracer(){
  for (int i = 0; i < primitives.size(); i++) {
    delete primitives[i];
  }
  for (int i = 0; i < lights.size(); i++) {
    delete lights[i];
  }
}

bool Raytracer::visible(vec4 p0, Light *l){
	int i;
	vec4 p1;
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
	

void Raytracer::trace(int reflects, vec4 p0, vec4 p1, double depth, Color *c){
	int i;
	double t;
	double minT = depth;
	int minPrimIndex = -1;
	double attn;
	vec4 lDirection;
	vec4 h;
	vec4 normal;

	if (reflects <= 0){
		return;
	}

	Color reflectColor = Color(0, 0, 0);
	vec4 reflectRay;

	for(i = 0; i < primitives.size(); i++){
		if (primitives.at(i)->intersect(p0, p1, &t, depth)){
			if (i == 2){
				i = i;
			}
			if (t < minT){
				minPrimIndex = i;
				minT = t;
			}
		}
	}

	if (minPrimIndex == -1){
		*c = Color(0,0,0);
	} else {
		*c = primitives.at(minPrimIndex)->ka + primitives.at(minPrimIndex)->ke;
		for (i = 0; i < lights.size(); i++){
			attn = 1.0/((lights.at(i)->attn)[0] + (lights.at(i)->attn)[1] * minT + (lights.at(i)->attn)[2] * minT * minT);
			if (visible(p0 + (minT*p1), lights.at(i))){
				h = (-(p0 + (minT * p1)) + (lights.at(i)->pos - (p0 + (minT * p1)))).normalize();

				if (lights.at(i)->directional)
					lDirection = vec4(lights.at(i)->pos);
				else
					lDirection = p0 + (minT*p1) - vec4(lights.at(i)->pos);

				normal =  primitives.at(minPrimIndex)->getNormal(p0 + (minT*p1));

				lDirection = -lDirection;

				*c = *c + ((attn * lights.at(i)->color) * ((primitives.at(minPrimIndex)->kd * MAX(lDirection * normal, 0))
					+ (primitives.at(minPrimIndex)->ks * pow((normal * h), primitives.at(minPrimIndex)->sp))));

				reflectRay = p0 + (minT*p1);
				reflectRay += 2 * (normal * (-(normal * (p0 + (minT*p1)))));
				reflectRay = reflectRay.normalize();
				trace(reflects - 1, p0 + (minT*p1), reflectRay, depth, &reflectColor);

				*c = *c + primitives.at(minPrimIndex)->kr*reflectColor;
				//*c = *c + Color(0, 0, 0);
			} else {
				
			}
		}
	}
}
