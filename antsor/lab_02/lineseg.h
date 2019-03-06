#ifndef LINESEG_H
#define LINESEG_H

#include "point.h"

class LineSeg
{
public:
	LineSeg();
	LineSeg(int x1, int y1, int x2, int y2);
	LineSeg(Point *p1, Point *p2);
	
	Point *p1();
	Point *p2();
	
	double length();
	
private:
	Point end1, end2;
};

#endif // LINESEG_H
