#include "rectangle.h"

Rectangle::Rectangle()
{
	for (int i = 0; i < 4; i++)
	{
		vert[i].setX(0);
		vert[i].setY(0);
	}
}

Rectangle::Rectangle(Point p1, int w, int h)
{
	vert[0].setX(p1.x());
	vert[0].setY(p1.y());
	
	vert[1].setX(p1.x() + w);
	vert[1].setY(p1.y());
	
	vert[2].setX(p1.x());
	vert[2].setY(p1.y() + h);
	
	vert[3].setX(p1.x() + w);
	vert[3].setY(p1.y() + h);
}


Point *Rectangle::vertex(int i)
{
	if (i < 0 || i > 3)
		return nullptr;
	return &vert[i];
}

void Rectangle::setVertex(Point p, int i)
{
	if (i >= 0 && i < 4)
	{
		vert[i].setX(p.x());
		vert[i].setY(p.y());
	}
}
