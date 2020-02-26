#include "lineseg.h"

LineSeg::LineSeg()
{
	end1 = Point(0, 0);
	end2 = Point(0, 1);
}

LineSeg::LineSeg(float x1, float y1, float x2, float y2)
{
	end1 = Point(x1, y1);
	end2 = Point(x2, y2);
}

LineSeg::LineSeg(Point *p1, Point *p2)
{
	end1 = *p1;
	end2 = *p2;
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
