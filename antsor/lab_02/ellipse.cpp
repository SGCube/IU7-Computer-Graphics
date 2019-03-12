#include "ellipse.h"
#include <cmath>

Ellipse::Ellipse(Point center = Point(0, 0), float a = 100, float b = 100)
	: Outline::Outline(POINTS_N, line, true)
{
	float dx = 2 * a / POINTS_N;
	float x = -a;
	for (int i = 0; i < POINTS_N && x <= a; x += dx, i++)
	{
		line[i].setX(x + center.x());
		line[i].setY(b * sqrt(1 - x * x / (a * a)) + center.y());
	}
}
