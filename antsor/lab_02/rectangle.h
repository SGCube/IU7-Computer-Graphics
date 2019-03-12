#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "outline.h"

class Rectangle : public Outline
{
public:
	Rectangle();
	Rectangle(Point p1, int w, int h);
	
private:
	Point vertex[4];
};

#endif // RECTANGLE_H
