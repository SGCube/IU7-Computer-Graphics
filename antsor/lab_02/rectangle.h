#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "point.h"
#include "lineseg.h"

class Rectangle
{
public:
	Rectangle();
	Rectangle(Point p1, Point p2, double ang = 0);
	Rectangle(double x1, double y1, double x2, double y2, double ang = 0);
	
	Point topleft();
	void setTopLeft(Point p);
	void setTopLeft(double x, double y);
	
	Point bottomright();
	void setBottomRight(Point p);
	void setBottomRight(double x, double y);
	
	double angle();
	void setAngle(double ang);
	
private:
	Point tlp, brp;
	double angle;
};

#endif // RECTANGLE_H
