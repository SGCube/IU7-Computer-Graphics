#include "rectangle.h"

Rectangle::Rectangle()
{
	tlp.setX(0);
	tlp.setY(0);
	brp.setX(10);
	brp.setY(10);
	angle = 0;
}

Rectangle::Rectangle(Point p1, Point p2, double ang = 0)
{
	tlp.setX(p1.x());
	tlp.setY(p1.y());
	brp.setX(p2.x());
	brp.setY(p2.y());
	angle = ang;
}

Rectangle::Rectangle(double x1, double y1, double x2, double y2, double ang = 0)
{
	tlp.setX(x1);
	tlp.setY(y1);
	brp.setX(x2);
	brp.setY(y2);
	angle = ang;
}


Point Rectangle::topleft()
{
	return tlp;
}

void Rectangle::setTopLeft(Point p)
{
	tlp.setX(p.x());
	tlp.setY(p.y());
}

void Rectangle::setTopLeft(double x, double y)
{
	tlp.setX(x);
	tlp.setY(y);
}


Point Rectangle::bottomright()
{
	return brp;
}

void Rectangle::setBottomRight(Point p)
{
	brp.setX(p.x());
	brp.setY(p.y());
}

void Rectangle::setBottomRight(double x, double y)
{
	brp.setX(x);
	brp.setY(y);
}

double Rectangle::angle()
{
	return angle;
}

void Rectangle::setAngle(double ang)
{
	angle = ang;
}
