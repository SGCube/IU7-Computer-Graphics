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
	
	void setLine();
	void setCutter();
	void setCutted();
	
private:
	QPen pen;
	QColor colorLine;
	QColor colorCutter;
	QColor colorCutted;
};

#endif // PAINTER_H
