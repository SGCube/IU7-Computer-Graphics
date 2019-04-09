#include <math.h>

#include "circle.h"

void draw_circle_canon(QPainter *painter, Point pc, double r)
{
	int r2 = r * r;
	double x_end = r / sqrt(2);
	
	for (double x = 0, y = r; x <= x_end; x += 1)
	{
		y = sqrt(r2 - x * x);
		
		painter->drawPoint(pc.x() + round(x), pc.y() + round(y));
		painter->drawPoint(pc.x() - round(x), pc.y() + round(y));
		painter->drawPoint(pc.x() + round(x), pc.y() - round(y));
		painter->drawPoint(pc.x() - round(x), pc.y() - round(y));
		
		painter->drawPoint(pc.x() + round(y), pc.y() + round(x));
		painter->drawPoint(pc.x() - round(y), pc.y() + round(x));
		painter->drawPoint(pc.x() + round(y), pc.y() - round(x));
		painter->drawPoint(pc.x() - round(y), pc.y() - round(x));
	}
}

void draw_circle_param(QPainter *painter, Point pc, double r)
{
	double dt = 1 / r;
	double t_end = 2 * M_PI;
	int x, y;
	
	for (double t = 0; t < 2 * t_end; t += dt)
	{
		x = pc.x() + (int)round(r * cos(t));
		y = pc.y() + (int)round(r * sin(t));
		painter->drawPoint(x, y);
	}
}

void draw_circle_lib(QPainter *painter, Point pc, double r)
{
	painter->drawEllipse(QPointF(pc.x(), pc.y()), r, r);
}
