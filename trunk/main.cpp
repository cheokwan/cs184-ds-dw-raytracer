#include <stdio.h>
#include <string.h>
#include "bmp/easyBMP.h"
#include "Sphere.h"

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

	Sphere s1 = Sphere();
	s1.setRadius(2);

	BMP *myPic = new BMP();
	myPic->SetSize(100, 100);
	for (i = 0; i < 100; i++){
		for (j = 0; j < 100; j++){
			if (s1.intersect(vec3(0, 0, 0), vec3(((double)i/50)-1, -(((double)j/50)-1), 2) - vec3(0, 0, 0)))
				myPic->SetPixel(i, j, *red);
			else
				myPic->SetPixel(i, j, *black);
		}
	}





	myPic->WriteToFile("testing.bmp");
	delete myPic;

	scanf("%d", &i);
	
	free(red);
	return 0;
}