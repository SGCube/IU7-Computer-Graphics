#include "arc.h"
#include <QtMath>

Arc::Arc(Point p, float a, float b, int angle)
	: Outline::Outline(POINTS_N, line, false)
{
	float ang = 0, pi_angle = qDegreesToRadians(angle);
	float dang = pi_angle / POINTS_N;
	
	for (int i = 0; i < POINTS_N && abs(ang) < abs(pi_angle); ang += dang, i++)
	{
		line[i].setX(a * cos(ang) + p.x());
		line[i].setY(b * sin(ang) + p.y());
	}
}
