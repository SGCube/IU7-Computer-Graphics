#include "ellipse.h"

Ellipse::Ellipse()
{
	pc.setX(0);
	pc.setY(0);
}

Ellipse::Ellipse(Point p, float a, float b)
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

float Ellipse::a()
{
	return ra;
}

float Ellipse::b()
{
	return rb;
}

void Ellipse::setA(float a)
{
	ra = a;
}

void Ellipse::setB(float b)
{
	rb = b;
}
