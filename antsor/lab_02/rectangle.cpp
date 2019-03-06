#include "rectangle.h"

Rectangle::Rectangle()
{
	tlp.setX(0);
	tlp.setY(0);
	brp.setX(10);
	brp.setY(10);
	angle = 0;
}

Rectangle::Rectangle(Point p1, Point p2, int ang = 0)
{
	tlp.setX(p1.x());
	tlp.setY(p1.y());
	brp.setX(p2.x());
	brp.setY(p2.y());
	angle = ang;
}

Rectangle::Rectangle(int x1, int y1, int x2, int y2, int ang = 0)
{
	tlp.setX(x1);
	tlp.setY(y1);
	brp.setX(x2);
	brp.setY(y2);
	angle = ang;
}


Point Rectangle::topleft()
{
	return &tlp;
}

void Rectangle::setTopLeft(Point p)
{
	tlp.setX(p.x());
	tlp.setY(p.y());
}

void Rectangle::setTopLeft(int x, int y)
{
	tlp.setX(x);
	tlp.setY(y);
}


Point Rectangle::bottomright()
{
	return &brp;
}

void Rectangle::setBottomRight(Point p)
{
	brp.setX(p.x());
	brp.setY(p.y());
}

void Rectangle::setBottomRight(int x, int y)
{
	brp.setX(x);
	brp.setY(y);
}

int Rectangle::angle()
{
	return angle;
}

void Rectangle::setAngle(int ang)
{
	angle = ang;
}
