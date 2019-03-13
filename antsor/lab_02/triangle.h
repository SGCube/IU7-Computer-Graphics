#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "outline.h"

class Triangle : public Outline
{
public:
	Triangle(Point p1, Point p2, Point p3);
	
private:
	Point vertex[3];
};

#endif // TRIANGLE_H
