#include "rectangle.h"

Rectangle::Rectangle(Point p1 = Point(0, 0), int w = 0, int h = 0)
	: Outline::Outline(4, vertex, true)
{
	vertex[0].setX(p1.x());
	vertex[0].setY(p1.y());
	
	vertex[1].setX(p1.x() + w);
	vertex[1].setY(p1.y());
	
	vertex[2].setX(p1.x() + w);
	vertex[2].setY(p1.y() + h);
	
	vertex[3].setX(p1.x());
	vertex[3].setY(p1.y() + h);
}
