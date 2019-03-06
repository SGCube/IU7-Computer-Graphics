#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "point.h"

class Ellipse
{
public:
	Ellipse();
	Ellipse(Point p, double a, double b);
	
	Point center();
	void setCenter(Point p);
	void setCenter(double x, double y);
	
	double a();
	double b();
	
	void setA(double a);
	void setB(double b);
	
private:
	Point pc;
	double ra, rb;
};

#endif // ELLIPSE_H
