#ifndef LINESEG_H
#define LINESEG_H

#include "point.h"

class LineSeg
{
public:
	LineSeg();
	LineSeg(Point p1, Point p2);
	
	Point *p1();
	Point *p2();
	
	double length();
	
private:
	Point end1, end2;
};

#endif // LINESEG_H
