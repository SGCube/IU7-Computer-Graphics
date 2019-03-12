﻿#include "ellipse.h"
#include <cmath>

#define PI 3.14

Ellipse::Ellipse(Point center = Point(0, 0), float a = 100, float b = 100)
	: Outline::Outline(POINTS_N, line, true)
{
	float ang = 0, pi2 = 2 * PI;
	float dang = pi2 / POINTS_N;
	
	for (int i = 0; i < POINTS_N && ang < pi2; ang += dang, i++)
	{
		line[i].setX(a * cos(ang) + center.x());
		line[i].setY(b * sin(ang) + center.y());
	}
}
