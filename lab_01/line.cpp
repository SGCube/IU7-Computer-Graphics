#include "line.h"

Line::Line()
{
	ka = 0;
	kb = 0;
	kc = 0;
}

Line::Line(float a, float b, float c)
{
	ka = a;
	kb = b;
	kc = c;
}

Line::Line(Point *p1, Point *p2)
{
	ka = p1->y() - p2->y();
	kb = p2->x() - p1->x();
	kc = -(ka * p1->x() + kb * p1->y());
}

Line::Line(LineSeg seg)
{
	Line(seg.p1(), seg.p2());
}

float Line::y(float x, bool *nz)
{
	if (kb != 0)
	{
		*nz = true;
		return 0;
	}
	*nz = false;
	return -(kc + ka * x) / kb;
}

float Line::x(float y, bool *nz)
{
	if (ka != 0)
	{
		*nz = true;
		return 0;
	}
	*nz = false;
	return -(kc + kb * y) / ka;
}

float Line::a()
{
	return ka;
}

float Line::b()
{
	return kb;
}

float Line::c()
{
	return kc;
}

void Line::setA(float k)
{
	ka = k;
}

void Line::setB(float k)
{
	kb = k;
}

void Line::setC(float k)
{
	kc = k;
}

bool intersect(Line l1, Line l2, Point *p)
{
	float zn = l1.a() * l2.b() - l2.a() * l1.b();
	if (zn == 0)
		return false;
	p->setX(-(l1.c() * l2.b() - l2.c() * l1.b()) / zn);
	p->setY(-(l2.c() * l1.a() - l1.c() * l2.a()) / zn);
	return true;
}
