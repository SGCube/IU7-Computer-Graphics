#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "point.h"

class Ellipse
{
public:
	Ellipse();
	Ellipse(Point p, int a, int b);
	
	Point *center();
	void setCenter(Point p);
	void setCenter(int x, int y);
	
	float a();
	float b();
	void setA(float a);
	void setB(float b);
	
	int angle();
	void setAngle(int ang);
	
private:
	Point pc;
	float ra, rb;
	int angle;
};

#endif // ELLIPSE_H
