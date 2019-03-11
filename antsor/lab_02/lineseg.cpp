#include "lineseg.h"

LineSeg::LineSeg()
{
	end1 = Point(0, 0);
	end2 = Point(0, 1);
}

LineSeg::LineSeg(Point p1, Point p2)
{
	end1 = p1;
	end2 = p2;
}

Point *LineSeg::p1()
{
	return &end1;
}

Point *LineSeg::p2()
{
	return &end2;
}

double LineSeg::length()
{
	return dist(end1, end2);
}
