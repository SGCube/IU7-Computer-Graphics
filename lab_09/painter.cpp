#include "painter.h"

Painter::Painter() :
	QPainter(),
	pen(QColor(0, 0, 0)),
	colorLine(0, 0, 0),
	colorClipper(0, 0, 255),
	colorClipped(255, 0, 0)
{
	
}

void Painter::drawLineSeg(int x1, int y1, int x2, int y2)
{
	setLine();
	drawLine(x1, y1, x2, y2);
}

void Painter::drawClipper(int x1, int y1, int x2, int y2)
{
	setClipper();
	drawLine(x1, y1, x2, y2);
}

void Painter::drawClipped(int x1, int y1, int x2, int y2)
{
	setClipped();
	drawLine(x1, y1, x2, y2);
}

void Painter::setLine()
{
	pen.setColor(colorLine);
	pen.setWidth(1);
	setPen(pen);
}

void Painter::setClipper()
{
	pen.setColor(colorClipper);
	pen.setWidth(1);
	setPen(pen);
}

void Painter::setClipped()
{
	pen.setColor(colorClipped);
	pen.setWidth(2);
	setPen(pen);
}
