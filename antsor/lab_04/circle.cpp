#include <math.h>

#include "circle.h"

void draw_circle_canon(QPainter *painter, Point pc, double r)
{
	double r2 = r * r;
	double x_end = r / sqrt(2);
	int xx, yy;
	
	for (double x = 0, y = r; x <= x_end; x += 1)
	{
		y = sqrt(r2 - x * x);
		xx = round(x);
		yy = round(y);
		
		painter->drawPoint(pc.x() + xx, pc.y() + yy);
		painter->drawPoint(pc.x() - xx, pc.y() + yy);
		painter->drawPoint(pc.x() + xx, pc.y() - yy);
		painter->drawPoint(pc.x() - xx, pc.y() - yy);
		
		painter->drawPoint(pc.x() + yy, pc.y() + xx);
		painter->drawPoint(pc.x() - yy, pc.y() + xx);
		painter->drawPoint(pc.x() + yy, pc.y() - xx);
		painter->drawPoint(pc.x() - yy, pc.y() - xx);
	}
}

void draw_circle_param(QPainter *painter, Point pc, double r)
{
	double dt = 1 / r;
	double t_end = M_PI / 4;
	int x, y;
	
	for (double t = 0; t <= t_end; t += dt)
	{
		x = round(r * cos(t));
		y = round(r * sin(t));
		
		painter->drawPoint(pc.x() + x, pc.y() + y);
		painter->drawPoint(pc.x() - x, pc.y() + y);
		painter->drawPoint(pc.x() + x, pc.y() - y);
		painter->drawPoint(pc.x() - x, pc.y() - y);
		
		painter->drawPoint(pc.x() + y, pc.y() + x);
		painter->drawPoint(pc.x() - y, pc.y() + x);
		painter->drawPoint(pc.x() + y, pc.y() - x);
		painter->drawPoint(pc.x() - y, pc.y() - x);
	}
}

void draw_circle_bresem(QPainter *painter, Point pc, double r)
{
	int x = 0, y = r;
	int d = 2 * (1 - r);
	int d1, d2;
	
	while(y >= 0)
	{
		painter->drawPoint(pc.x() + x, pc.y() - y);
		painter->drawPoint(pc.x() - x, pc.y() - y);
		painter->drawPoint(pc.x() + x, pc.y() + y);
		painter->drawPoint(pc.x() - x, pc.y() + y);
		
		if (d < 0)
		{
			d1 = 2 * (d + y) - 1;
			if (d1 >= 0)
			{
				y--;
				d += -2 * y + 1;
			}
			x++;
			d += 2 * x + 1;
		}
		else if (d > 0)
		{
			d2 = 2 * (d - x) - 1;
			if (d2 < 0)
			{
				x++;
				d += 2 * x + 1;
			}
			y--;
			d += -2 * y + 1;
		}
		else
		{
			x++;
			y--;
			d += 2 * (x - y + 1);
		}
	}
}

void draw_circle_midpoint(QPainter *painter, Point pc, double r)
{
	int x = 0, y = r;
	double f = 1.25 - r;
	double dx = 0, dy = -2 * r;
	
	while (x <= y)
	{
		painter->drawPoint(pc.x() + x, pc.y() - y);
		painter->drawPoint(pc.x() - x, pc.y() - y);
		painter->drawPoint(pc.x() + x, pc.y() + y);
		painter->drawPoint(pc.x() - x, pc.y() + y);
		
		painter->drawPoint(pc.x() + y, pc.y() + x);
		painter->drawPoint(pc.x() - y, pc.y() + x);
		painter->drawPoint(pc.x() + y, pc.y() - x);
		painter->drawPoint(pc.x() - y, pc.y() - x);
		
		if (f >= 0)
		{
			y--;
			// f -= 2 * y
			dy += 2;
			f += dy;
		}
		x++;
		// f += 2 * x + 1
		dx += 2;
		f += dx + 1;
	}
}

void draw_circle_lib(QPainter *painter, Point pc, double r)
{
	painter->drawEllipse(QPointF(pc.x(), pc.y()), r, r);
}
