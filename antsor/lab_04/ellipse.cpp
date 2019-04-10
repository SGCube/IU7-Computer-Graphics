#include <math.h>

#include "ellipse.h"

void draw_ellipse_canon(QPainter *painter, Point pc, double a, double b)
{
	double a2 = a * a;
	double b2 = b * b;
	double x_end = a2 / sqrt(a2 + b2);
	double m = b / a;
	double x, y;
	int xx, yy;
	
	for (x = 0; x <= x_end; x += 1)
	{
		y = sqrt(a2 - x * x) * m;
		xx = round(x);
		yy = round(y);
		
		painter->drawPoint(pc.x() + xx, pc.y() + yy);
		painter->drawPoint(pc.x() - xx, pc.y() + yy);
		painter->drawPoint(pc.x() + xx, pc.y() - yy);
		painter->drawPoint(pc.x() - xx, pc.y() - yy);
	}
	
	double y_end = b2 / sqrt(a2 + b2);
	m = 1 / m;
		
	for (y = 0; y <= y_end; y += 1)
	{
		x = sqrt(b2 - y * y) * m;
		xx = round(x);
		yy = round(y);
		
		painter->drawPoint(pc.x() + xx, pc.y() + yy);
		painter->drawPoint(pc.x() - xx, pc.y() + yy);
		painter->drawPoint(pc.x() + xx, pc.y() - yy);
		painter->drawPoint(pc.x() - xx, pc.y() - yy);
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

void draw_ellipse_bresem(QPainter *painter, Point pc, double a, double b)
{
	int a2 = a * a;
	int b2 = b * b;
	
	int x = 0, y = b;
	int d = 4 * b2 + a2 * (1 - 4 * b);
	while (b2 * x <= a2 * y)
	{
		painter->drawPoint(pc.x() + x, pc.y() - y);
		painter->drawPoint(pc.x() - x, pc.y() - y);
		painter->drawPoint(pc.x() + x, pc.y() + y);
		painter->drawPoint(pc.x() - x, pc.y() + y);
		
		if (d >= 0)
		{
			d -= 8 * a2 * (y - 1);
			y--;
		}
		d += b2 * (8 * x + 12);
		x++;
	}
	
	x = a, y = 0;
	d = 4 * a2 + b2 * (1 - 4 * a);
	while (a2 * y <= b2 * x)
	{
		painter->drawPoint(pc.x() + x, pc.y() - y);
		painter->drawPoint(pc.x() - x, pc.y() - y);
		painter->drawPoint(pc.x() + x, pc.y() + y);
		painter->drawPoint(pc.x() - x, pc.y() + y);
		
		if (d >= 0)
		{
			d -= 8 * b2 * (x + 1);
			x--;
		}
		d += a2 * (8 * y + 12);
		y++;
	}
	
	
}

void draw_ellipse_lib(QPainter *painter, Point pc, double a, double b)
{
	painter->drawEllipse(QPointF(pc.x(), pc.y()), a, b);
}
