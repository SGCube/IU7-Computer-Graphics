#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "point.h"
#include "lineseg.h"

class Triangle
{
public:
	Triangle();
    Triangle(Point p1, Point p2, Point p3);
	
	Point *point(int i);
	void setPoint(Point p, int i);
	
private:
	Point points[3];
};

#endif // TRIANGLE_H
