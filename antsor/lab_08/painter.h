#ifndef PAINTER_H
#define PAINTER_H

#include <QPainter>

class Painter : public QPainter
{
public:
	Painter();
	void setColorLine(QColor color) { colorLine = color; }
	void setColorClipper(QColor color) { colorClipper = color; }
	void setColorClipped(QColor color) { colorClipped = color; }
	
	void drawLineSeg(int x1, int y1, int x2, int y2);
	void drawClipper(int x1, int y1, int x2, int y2);
	void drawClipped(int x1, int y1, int x2, int y2);
	
	QColor getColorLine() const { return colorLine; }
	QColor getColorClipper() const { return colorClipper; }
	QColor getColorClipped() const { return colorClipped; }
	
private:
	QPen pen;
	QColor colorLine;
	QColor colorClipper;
	QColor colorClipped;
	
	void setLine();
	void setClipper();
	void setClipped();
};

#endif // PAINTER_H
