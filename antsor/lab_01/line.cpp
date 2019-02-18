#include "line.h"

Line::Line()
{
	a = 0;
	b = 0;
	c = 0;
}

Line::Line(float ka, float kb, float kc)
{
	a = ka;
	b = kb;
	c = kc;
}

Line(QPointF p1, QPointF p2)
{
	a = p1.y() - p2.y();
	b = p2.x() - p1.x();
	c = -(a * p1.x() + b * p1.y());
}

float Line::y(float x, bool *nz)
{
	if (b != 0)
	{
		*nz = true;
		return 0;
	}
	*nz = false;
	return -(c + a * x) / b;
}

float Line::x(float y, bool *nz)
{
	if (a != 0)
	{
		*nz = true;
		return 0;
	}
	*nz = false;
	return -(c + b * y) / a;
}


bool intersect(Line l1, Line l2. QPointF *p)
{
	float zn = l1.a * l2.b - l2.a * l1.b;
	if (zn == 0)
		return false;
	float x = (l1.c * l2.b - l2.c * l1.b) / zn;
	float y = (l2.c * l1.a - l1.c * l2.a) / zn;
	return true;
}
