#include "algebra3.h"
#include "Color.h"

#ifndef _Light_h_
#define _Light_h_

class Light
{
public:
	bool directional;
	vec4 pos;
	Color color;
	vec3 attn;
	Light();
	Light(double x, double y, double z, Color c, bool lightType);
	~Light();
};

#endif