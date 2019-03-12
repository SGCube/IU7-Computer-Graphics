#include "arc.h"
#include <cmath>

#define PI 3.14

Arc::Arc(Point p, float a, float b, int angle)
	: Outline::Outline(POINTS_N, line, false)
{
	float ang = 0;
	float pi_angle = (float)angle * PI / 180;
	float dang = pi_angle / POINTS_N;
	
	for (int i = 0; i < POINTS_N && abs(ang) < abs(pi_angle); ang += dang, i++)
	{
		line[i].setX(a * cos(ang) + p.x());
		line[i].setY(b * sin(ang) + p.y());
	}
}
