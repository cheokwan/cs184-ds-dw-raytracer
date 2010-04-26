#include "Light.h"

Light::Light(double x, double y, double z, Color c, bool lightType){
	pos = vec3(x, y, z);
	color = c;
	directional = !lightType;
	attn = vec3(1, 0, 0);
}

Light::Light(){
	color = Color(0, 0, 0);
	pos = vec3(0, 0, 0);
	attn = vec3(1, 0, 0);
	directional = false;
}

Light::~Light(){
}