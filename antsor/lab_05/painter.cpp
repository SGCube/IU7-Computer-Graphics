#include "painter.h"

Painter::Painter() :
	QPainter(),
	pen(QColor(0, 0, 0))
{
	
}

void Painter::set_color(QColor color)
{
	pen.setColor(color);
}

void Painter::set_pen()
{
	setPen(pen);
}
