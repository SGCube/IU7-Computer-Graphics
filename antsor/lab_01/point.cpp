#include "point.h"

#include <math.h>

Point::Point()
{
	x = 0;
	y = 0;
}

Point::Point(float px, float py)
{
	x = px;
	y = py;
}

float Point::getX()
{
	return x;
}

float Point::getY()
{
	return y;
}

void Point::setX(float px)
{
	x = px;
}

void Point::setY(float py)
{
	y = py;
}

float dist(Point p1, Point p2)
{
	float dx = p2.getX() - p1.getX();
	float dy = p2.getY() - p1.getY();
	return sqrt(dx * dx + dy * dy);
}
