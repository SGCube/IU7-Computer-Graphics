#include "lineseg.h"

LineSeg::LineSeg()
{
	vertex[0] = Point(0, 0);
	vertex[1] = Point(0, 1);
	
	vertex_amount = 2;
	vertex_ptr = vertex;
	is_closed = false;
}

LineSeg::LineSeg(Point p1, Point p2)
{
	vertex[0] = p1;
	vertex[1] = p2;
	
	vertex_amount = 2;
	vertex_ptr = vertex;
	is_closed = false;
}

Point *LineSeg::p1()
{
	return &vertex[0];
}

Point *LineSeg::p2()
{
	return &vertex[1];
}

double LineSeg::length()
{
	return dist(vertex[0], vertex[1]);
}
