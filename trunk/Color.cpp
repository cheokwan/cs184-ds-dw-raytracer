#include "Color.h"

RGBApixel Color::toRGBA(){
	RGBApixel pix;
	pix.Red = r*255;
	pix.Green = g*255;
	pix.Blue = b*255;
	pix.Alpha = 0;
	return pix;
}

Color::Color(double newR, double newG, double newB){
	r = newR;
	g = newG;
	b = newB;
}

Color::Color(){
	r = 0;
	g = 0;
	b = 0;
}

Color::~Color(){
}