#include "triangle.h"

Triangle::Triangle()
{
    points[0] = Point();
    points[1] = Point();
    points[2] = Point();
}

Triangle::Triangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
    points[0] = Point(x1, y1);
    points[1] = Point(x2, y2);
    points[2] = Point(x3, y3);
}

Triangle::Triangle(Point p1, Point p2, Point p3)
{
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
}

Point *Triangle::point(int i)
{
	if (i < 0 || i > 2)
		return nullptr;
	return &(points[i]);
}

bool isTriangle(Point *p1, Point *p2, Point *p3)
{
	LineSeg a = LineSeg(p1, p2);
	LineSeg b = LineSeg(p1, p3);
	LineSeg c = LineSeg(p2, p3);
	return (a.length() + b.length() > c.length() &&
            a.length() + c.length() > b.length() &&
            b.length() + c.length() > a.length());
}

bool isTriangle(Triangle *tr)
{
	LineSeg a = LineSeg(tr->point(0), tr->point(1));
	LineSeg b = LineSeg(tr->point(0), tr->point(2));
	LineSeg c = LineSeg(tr->point(1), tr->point(2));
	
	return (a.length() + b.length() > c.length() &&
            a.length() + c.length() > b.length() &&
            b.length() + c.length() > a.length());
}


