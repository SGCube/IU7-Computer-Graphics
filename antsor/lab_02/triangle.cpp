#include "triangle.h"

Triangle::Triangle(Point p1 = Point(0, 0), Point p2 = Point(0, 0),
				   Point p3 = Point(0, 0)) : Outline::Outline(3, vertex, true)
{
    vertex[0] = p1;
    vertex[1] = p2;
    vertex[2] = p3;
}
