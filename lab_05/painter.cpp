#include "painter.h"

#include <math.h>

Painter::Painter() :
	QPainter(),
	pen(QColor(0, 0, 0)),
	color_fill(0, 0, 255),
	color_bg(255, 255, 255),
	color_edge(0, 0, 0)
{
	
}

void Painter::set_color_edge(QColor color)
{
	pen.setColor(color);
	color_edge = color;
}

void Painter::set_color_fill(QColor color)
{
	color_fill = color;
}

void Painter::set_color_bg(QColor color)
{
	color_bg = color;
}

void Painter::set_fill()
{
	pen.setColor(color_fill);
	setPen(pen);
}

void Painter::set_bg()
{
	pen.setColor(color_bg);
	setPen(pen);
}

void Painter::set_edge()
{
	pen.setColor(color_edge);
	setPen(pen);
}

bool Painter::is_bg(QColor color)
{
	return color_bg == color;
}

bool Painter::is_fill(QColor color)
{
	return color_fill == color;
}

bool Painter::is_edge(QColor color)
{
	return color_edge == color;
}

void Painter::draw_line(Point p1, Point p2)
{
	if (p1 == p2)
	{
		drawPoint(p1.x(), p1.y());
		return;
	}
	double xlen = p2.x() - p1.x(), ylen = p2.y() - p1.y();
	double len = 0;
	if (fabs(xlen) > fabs(ylen))
		len =fabs(xlen);
	else
		len = fabs(ylen);
	double dx = xlen / len, dy = ylen / len;
	
	double x = p1.x(), y = p1.y();
	for (int i = 1; i <= dx + len + 1; i++)
	{
		drawPoint(round(x), round(y));
		x += dx;
		y += dy;
	}
}

void Painter::draw_polygons(QImage *img, std::vector<Polygon> &set)
{
	begin(img);
	set_edge();
	for (size_t i = 0; i < set.size(); i++)
	{
		int j = 1;
		for (; j < set[i].number_of_vertexes(); j++)
			draw_line(set[i][j - 1], set[i][j]);
		draw_line(set[i][j - 1], set[i][0]);
	}
	end();
}
