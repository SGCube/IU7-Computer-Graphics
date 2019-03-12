#include "triangle.h"

Triangle::Triangle()
{
    vertex[0] = Point();
    vertex[1] = Point();
    vertex[2] = Point();
	vertex_amount = 3;
	vertex_ptr = vertex;
}

Triangle::Triangle(Point p1, Point p2, Point p3)
{
    vertex[0] = p1;
    vertex[1] = p2;
    vertex[2] = p3;
	vertex_amount = 3;
	vertex_ptr = vertex;
}
