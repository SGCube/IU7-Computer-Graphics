#include "rectangle.h"

Rectangle::Rectangle()
{
	for (int i = 0; i < 4; i++)
	{
		vertex[i].setX(0);
		vertex[i].setY(0);
	}
	vertex_amount = 4;
	vertex_ptr = vertex;
}

Rectangle::Rectangle(Point p1, int w, int h)
{
	vertex[0].setX(p1.x());
	vertex[0].setY(p1.y());
	
	vertex[1].setX(p1.x() + w);
	vertex[1].setY(p1.y());
	
	vertex[2].setX(p1.x());
	vertex[2].setY(p1.y() + h);
	
	vertex[3].setX(p1.x() + w);
	vertex[3].setY(p1.y() + h);
	
	vertex_amount = 4;
	vertex_ptr = vertex;
}
