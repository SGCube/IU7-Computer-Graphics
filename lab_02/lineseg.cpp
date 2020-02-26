#include "lineseg.h"

LineSeg::LineSeg(Point p1 = Point(0, 0), Point p2 = Point(0, 1))
	: Outline::Outline(2, vertex, false)
{
	vertex[0] = p1;
	vertex[1] = p2;
}

double LineSeg::length()
{
	return dist(vertex[0], vertex[1]);
}
