#include "ellipse.h"
#include <cmath>

Ellipse::Ellipse(Point center = Point(0, 0), float a = 100, float b = 100)
{
	vertex_amount = POINTS_N;
	vertex_ptr = line;
	
	float dx = 2 * a / POINTS_N;
	for (float x = -a; x <= a; x += dx)
	{
		line[i].setX(x + center.x());
		line[i].setY(b * sqrt(1 - x * x / (a * a)) + center.y());
	}
}
