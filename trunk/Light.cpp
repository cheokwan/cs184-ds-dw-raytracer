#include "Light.h"

Light::Light(double x, double y, double z, Color c, bool lightType){
	pos = vec4(x, y, z, 1);
	color = c;
	directional = !lightType;
	attn = vec3(1, 0, 0);
}

Light::Light(){
	color = Color(0, 0, 0);
	pos = vec4(0, 0, 0, 0);
	attn = vec3(1, 0, 0);
	directional = false;
}

Light::~Light(){
}