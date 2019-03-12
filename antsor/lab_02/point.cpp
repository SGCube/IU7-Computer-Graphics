#include "point.h"

#include <math.h>

Point::Point()
{
	xcoord = 0;
	ycoord = 0;
}

Point::Point(double x, double y)
{
	xcoord = x;
	ycoord = y;
}

double Point::x()
{
	return xcoord;
}

double Point::y()
{
	return ycoord;
}

void Point::setX(double x)
{
	xcoord = x;
}

void Point::setY(double y)
{
	ycoord = y;
}

double dist(Point p1, Point p2)
{
	double dx = p2.x() - p1.x();
	double dy = p2.y() - p1.y();
	return sqrt(dx * dx + dy * dy);
}
