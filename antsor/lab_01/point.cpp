#include "point.h"

#include <math.h>

Point::Point()
{
	xcoord = 0;
	ycoord = 0;
}

Point::Point(float x, float y)
{
	xcoord = x;
	ycoord = y;
}

float Point::x()
{
	return xcoord;
}

float Point::y()
{
	return ycoord;
}

void Point::setX(float x)
{
	xcoord = x;
}

void Point::setY(float py)
{
	ycoord = y;
}

float dist(Point p1, Point p2)
{
	float dx = p2.x() - p1.x();
	float dy = p2.y() - p1.y();
	return sqrt(dx * dx + dy * dy);
}
