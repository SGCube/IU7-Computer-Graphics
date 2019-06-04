#ifndef PAINTER_H
#define PAINTER_H

#include <QPainter>

class Painter : public QPainter
{
public:
	Painter();
	void setColorLine(QColor color) { colorLine = color; }
	void setColorCutter(QColor color) { colorCutter = color; }
	void setColorCutted(QColor color) { colorCutted = color; }
	
	void drawLineSeg(int x1, int y1, int x2, int y2);
	void drawCutter(int x1, int y1, int x2, int y2);
	void drawCutted(int x1, int y1, int x2, int y2);
	
	QColor getColorLine() const { return colorLine; }
	QColor getColorCutter() const { return colorCutter; }
	QColor getColorCutted() const { return colorCutted; }
	
private:
	QPen pen;
	QColor colorLine;
	QColor colorCutter;
	QColor colorCutted;
	
	void setLine();
	void setCutter();
	void setCutted();
};

#endif // PAINTER_H
