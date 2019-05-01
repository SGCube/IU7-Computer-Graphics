#include <math.h>

#include "ellipse.h"

void draw_ellipse_canon(QPainter *painter, Point pc, double a, double b)
{
	double a2 = a * a, b2 = b * b;
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
	double t_end = M_PI / 2;
	int x, y;
	
	for (double t = 0; t <= t_end; t += dt)
	{
		x = round(a * cos(t));
		y = round(b * sin(t));
		
		painter->drawPoint(pc.x() + x, pc.y() + y);
		painter->drawPoint(pc.x() - x, pc.y() + y);
		painter->drawPoint(pc.x() + x, pc.y() - y);
		painter->drawPoint(pc.x() - x, pc.y() - y);
	}
}

void draw_ellipse_bresem(QPainter *painter, Point pc, double a, double b)
{
	int a2 = a * a;
	int b2 = b * b;
	
	int x = 0, y = b;
	int d = b2 - 2 * a2 * b + a2;
	int d1, d2;
	
	while (y > 0)
	{
		painter->drawPoint(pc.x() + x, pc.y() - y);
		painter->drawPoint(pc.x() - x, pc.y() - y);
		painter->drawPoint(pc.x() + x, pc.y() + y);
		painter->drawPoint(pc.x() - x, pc.y() + y);
		
		if (d < 0)
		{
			d1 = 2 * (d + a2 * y) - a2;
			if (d1 >= 0)
			{
				y--;
				d += -a2 * (2 * y - 1);
			}
			x++;
			d += b2 * (2 * x + 1);
		}
		else if (d > 0)
		{
			d2 = 2 * (d - b2 * x) - b2;
			if (d2 < 0)
			{
				x++;
				d += b2 * (2 * x + 1);
			}
			y--;
			d -= a2 * (2 * y - 1);
		}
		else
		{
			x++;
			y--;
			d += b2 * (2 * x + 1) - a2 * (2 * y - 1);
		}
	}
}

void draw_ellipse_midpoint(QPainter *painter, Point pc, double a, double b)
{
	int a2 = a * a, b2 = b * b;
	int ad = 2 * a2, bd = 2 * b2;
	
	int mid = a2 / sqrt(a2 + b2);
	
	int x = 0, y = b;
	
	double f = b2 - a2 * b + 0.25 * a2;
	double dx = 0, dy = -ad * y;
	
	while (x <= mid)
	{
		painter->drawPoint(pc.x() + x, pc.y() - y);
		painter->drawPoint(pc.x() - x, pc.y() - y);
		painter->drawPoint(pc.x() + x, pc.y() + y);
		painter->drawPoint(pc.x() - x, pc.y() + y);
		
		if (f > 0)
		{
			y--;
			// f -= ad * y;
			dy += ad;
			f += dy;
		}
		x++;
		// f += bd * x + b2;
		dx += bd;
		f += dx + b2;
	}
	
	f += -b2 * (x + 0.75) - a2 * (y - 0.75);
	
	while (y >= 0)
	{
		painter->drawPoint(pc.x() + x, pc.y() - y);
		painter->drawPoint(pc.x() - x, pc.y() - y);
		painter->drawPoint(pc.x() + x, pc.y() + y);
		painter->drawPoint(pc.x() - x, pc.y() + y);
		
		if (f <= 0)
		{
			x++;
			// f += bd * x;
			dx += bd;
			f += dx;
		}
		y--;
		// f += a2 - ad * y;
		dy += ad;
		f += a2 + dy;
	}
}

void draw_ellipse_lib(QPainter *painter, Point pc, double a, double b)
{
	painter->drawEllipse(QPointF(pc.x(), pc.y()), a, b);
}
