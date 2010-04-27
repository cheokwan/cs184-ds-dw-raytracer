#include <math.h>
#include "bmp/EasyBMP.h"

#ifndef _Color_h_
#define _Color_h_

class Color
{

	friend Color operator + (const Color& a, const Color& b);
	friend Color operator - (const Color& a, const Color& b);
	friend Color operator * (const Color& a, const double d);
	friend Color operator * (const double d, const Color& a);
	friend Color operator * (const Color& a, const Color& b);
	friend Color operator / (const Color& a, const double d);

public:
	double r;
	double g;
	double b;


	RGBApixel toRGBA();

	Color();
	Color(double r, double g, double b);
	~Color();

};


inline Color operator + (const Color& a, const Color& b)
{ return Color((a.r+b.r) > 1 ? 1 : (a.r+b.r), (a.g+b.g) > 1 ? 1 : (a.g+b.g), (a.b+b.b) > 1 ? 1 : (a.b+b.b)); }

inline Color operator - (const Color& a, const Color& b)
{ return Color((a.r-b.r) < 0 ? 0 : (a.r-b.r), (a.g-b.g) < 0 ? 0 : (a.g-b.g), (a.b-b.b) < 0 ? 0 : (a.b-b.b)); }

inline Color operator * (const Color& a, const double d)
{if (d < 0) 
	return Color(0, 0, 0);
return Color((a.r*d) > 1 ? 1 : (a.r*d), (a.g*d) > 1 ? 1 : (a.g*d), (a.b*d) > 1 ? 1 : (a.b*d)); }

inline Color operator * (const Color& a, const Color& b)
{ return Color(a.r*b.r, a.g*b.g, a.b*b.b); }

inline Color operator * (const double d, const Color& a)
{ return a*d; }

inline Color operator / (const Color& a, const double d)
{if (d <= 0) 
	return Color(0, 0, 0);
return Color((a.r/d) > 1 ? 1 : (a.r/d), (a.g/d) > 1 ? 1 : (a.g/d), (a.b/d) > 1 ? 1 : (a.b/d)); }

#endif
