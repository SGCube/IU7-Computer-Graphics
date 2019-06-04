#include "painter.h"

Painter::Painter() :
	QPainter(),
	pen(QColor(0, 0, 0)),
	colorLine(0, 0, 0),
	colorCutter(0, 0, 255),
	colorCutted(255, 0, 0)
{
	
}

void Painter::setColorLine(QColor color)
{
	pen.setColor(color);
	colorLine = color;
}

void Painter::setColorCutter(QColor color)
{
	colorCutter = color;
}

void Painter::setColorCutted(QColor color)
{
	colorCutted = color;
}

void Painter::drawLineSeg(int x1, int y1, int x2, int y2)
{
	setLine();
	drawLine(x1, y1, x2, y2);
}

void Painter::drawCutter(int x1, int y1, int x2, int y2)
{
	setCutter();
	drawRect(x1, y1, x2 - x1, y2 - y1);
}

void Painter::drawCutted(int x1, int y1, int x2, int y2)
{
	setCutted();
	drawLine(x1, y1, x2, y2);
}

void Painter::setLine()
{
	pen.setColor(colorLine);
	setPen(pen);
}

void Painter::setCutter()
{
	pen.setColor(colorCutter);
	setPen(pen);
}

void Painter::setCutted()
{
	pen.setColor(colorCutted);
	setPen(pen);
}
