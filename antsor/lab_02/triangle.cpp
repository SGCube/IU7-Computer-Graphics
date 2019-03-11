#include "triangle.h"

Triangle::Triangle()
{
    points[0] = Point();
    points[1] = Point();
    points[2] = Point();
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

void Triangle::setPoint(Point p, int i)
{
	if (i >= 0 && i < 3)
	{
		points[i].setX(p.x());
		points[i].setY(p.y());
	}
}
