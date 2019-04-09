#include <math.h>

#include "ellipse.h"

void draw_ellipse_canon(QPainter *painter, Point pc, double a, double b)
{
	double a2 = a * a;
	double b2 = b * b;
	double x_end = a2 / sqrt(a2 + b2);
	double m = b / a;
	double x, y;
	
	for (x = 0; x <= x_end; x += 1)
	{
		y = sqrt(a2 - x * x) * m;
		
		painter->drawPoint(pc.x() + round(x), pc.y() + round(y));
		painter->drawPoint(pc.x() - round(x), pc.y() + round(y));
		painter->drawPoint(pc.x() + round(x), pc.y() - round(y));
		painter->drawPoint(pc.x() - round(x), pc.y() - round(y));
	}
	
	double y_end = b2 / sqrt(a2 + b2);
	m = 1 / m;
		
	for (y = 0; y <= y_end; y += 1)
	{
		x = sqrt(b2 - y * y) * m;
		
		painter->drawPoint(pc.x() + round(x), pc.y() + round(y));
		painter->drawPoint(pc.x() - round(x), pc.y() + round(y));
		painter->drawPoint(pc.x() + round(x), pc.y() - round(y));
		painter->drawPoint(pc.x() - round(x), pc.y() - round(y));
	}
}

void draw_ellipse_param(QPainter *painter, Point pc, double a, double b)
{
	double dt = 1 / fmax(a, b);
	double t_end = 2 * M_PI;
	int x, y;
	
	for (double t = 0; t < 2 * t_end; t += dt)
	{
		x = pc.x() + (int)round(a * cos(t));
		y = pc.y() + (int)round(b * sin(t));
		painter->drawPoint(x, y);
	}
}

void draw_ellipse_lib(QPainter *painter, Point pc, double a, double b)
{
	painter->drawEllipse(QPointF(pc.x(), pc.y()), a, b);
}
