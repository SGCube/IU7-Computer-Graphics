#include "painter.h"

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
