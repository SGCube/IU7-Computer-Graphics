#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "point.h"
#include "lineseg.h"

class Triangle
{
public:
	Triangle();
    Triangle(int x1, int y1, int x2, int y2, int x3, int y3);
    Triangle(Point p1, Point p2, Point p3);
	
	Point *point(int i);
	
private:
	Point points[3];
};

bool isTriangle(Point *p1, Point *p2, Point *p3);

bool isTriangle(Triangle *tr);

#endif // TRIANGLE_H
