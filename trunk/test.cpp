#include <stdio.h>
#include <string.h>
#include "bmp/easyBMP.h"
#include "Sphere.h"
#include "Triangle.h"
#include "RayTracer.h"
#include "Color.h"

int main() {
	int i, j;
	RGBApixel *red, *black;
	red = (RGBApixel*) malloc (sizeof(RGBApixel));
	red->Red = 255;
	red->Blue = 0;
	red->Green = 0;
	red->Alpha = 0;
	black = (RGBApixel*) malloc (sizeof(RGBApixel));
	black->Red = 0;
	black->Blue = 0;
	black->Green = 0;
	black->Alpha = 0;

	double t;
	vec3 intersection;

	//Sphere s1 = Sphere();
	//s1.setRadius(2);

	Triangle s1 = Triangle();

	Raytracer* r = new Raytracer();

	Color c;

	BMP *myPic = new BMP();
	myPic->SetSize(400, 400);
	for (i = 0; i < 400; i++){
		for (j = 0; j < 400; j++){
			/*if (s1.intersect(vec3(0, 0, 0), vec3(((double)i/50)-1, -(((double)j/50)-1), 2) - vec3(0, 0, 0), &t, 200))
				myPic->SetPixel(i, j, *red);
			else
				myPic->SetPixel(i, j, *black);*/
			r->trace(vec3(0, 0, 0), vec3(((double)i/200)-1, -(((double)j/200)-1), 2), 100, &c);
			myPic->SetPixel(i, j, c.toRGBA());
		}
	}





	myPic->WriteToFile("testing.bmp");
	delete myPic;
	delete r;

	scanf("%d", &i);
	
	free(red);
	return 0;
}