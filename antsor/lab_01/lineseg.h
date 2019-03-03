#ifndef LINESEG_H
#define LINESEG_H

#include "point.h"

class LineSeg
{
public:
	LineSeg();
	LineSeg(float x1, float y1, float x2, float y2);
	LineSeg(Point p1, Point p2);
	
	Point *p1();
	Point *p2();
	
	float length();
	
private:
	Point end1, end2;
};

#endif // LINESEG_H
