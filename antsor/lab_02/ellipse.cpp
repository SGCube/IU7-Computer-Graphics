#include "ellipse.h"

Ellipse::Ellipse()
{
	pc.setX(0);
	pc.setY(0);
}

Ellipse::Ellipse(Point p, double a, double b)
{
	pc.setX(p.x());
	pc.setY(p.y());
	ra = a;
	rb = b;
}

Point Ellipse::center()
{
	return &pc;
}

void Ellipse::setCenter(Point p)
{
	pc.setX(p.x());
	pc.setY(p.y());
}

void Ellipse::setCenter(int x, int y)
{
	pc.setX(x);
	pc.setY(y);
}

double Ellipse::a()
{
	return ra;
}

double Ellipse::b()
{
	return rb;
}

void Ellipse::setA(double a)
{
	ra = a;
}

void Ellipse::setB(double b)
{
	rb = b;
}

int Ellipse::angle()
{
	return angle;
}

void Ellipse::setAngle(int ang)
{
	angle = ang;
}
