#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "point.h"
#include "lineseg.h"

class Rectangle
{
public:
	Rectangle();
	Rectangle(Point p1, int w, int h);
	
	Point *vertex(int i);
	void setVertex(Point p, int i);
	
private:
	Point vert[4];
};

#endif // RECTANGLE_H
