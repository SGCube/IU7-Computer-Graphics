#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "point.h"
#include "lineseg.h"

class Rectangle
{
public:
	Rectangle();
	Rectangle(Point p1, Point p2, int ang = 0);
	Rectangle(int x1, int y1, int x2, int y2, int ang = 0);
	
	Point *topleft();
	void setTopLeft(Point p);
	void setTopLeft(int x, int y);
	
	Point *bottomright();
	void setBottomRight(Point p);
	void setBottomRight(int x, int y);
	
	int angle();
	void setAngle(int ang);
	
private:
	Point tlp, brp;
	int angle;
};

#endif // RECTANGLE_H
