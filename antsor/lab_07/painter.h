#ifndef PAINTER_H
#define PAINTER_H

#include <QPainter>

class Painter : public QPainter
{
public:
	Painter();
	void setColorLine(QColor color);
	void setColorCutter(QColor color);
	void setColorCutted(QColor color);
	
	void drawLineSeg(int x1, int y1, int x2, int y2);
	void drawCutter(int x1, int y1, int x2, int y2);
	void drawCutted(int x1, int y1, int x2, int y2);
	
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
