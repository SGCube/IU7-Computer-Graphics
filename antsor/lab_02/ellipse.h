#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "point.h"

#define POINTS_N 1000

class Ellipse
{
public:
	Ellipse();
	Ellipse(Point p, float a, float b);
	
	Point *center();
	void setCenter(Point p);
	
	float a();
	float b();
	void setA(float a);
	void setB(float b);
	
private:
	Point pc;
	float ra, rb;
	Point outline[4 * POINTS_N];
};

#endif // ELLIPSE_H
