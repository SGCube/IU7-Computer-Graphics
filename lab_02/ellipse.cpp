#include "ellipse.h"
#include <QtMath>

Ellipse::Ellipse(Point center = Point(0, 0), double a = 100, double b = 100)
	: Outline::Outline(POINTS_N, line, true)
{
	double ang = 0, pi2 = 2 * M_PI;
	double dang = pi2 / POINTS_N;
	
	for (int i = 0; i < POINTS_N && ang < pi2; ang += dang, i++)
	{
		line[i].setX(a * cos(ang) + center.x());
		line[i].setY(b * sin(ang) + center.y());
	}
}
