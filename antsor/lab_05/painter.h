#ifndef PAINTER_H
#define PAINTER_H

#include <QPainter>

class Painter : public QPainter
{
public:
	Painter();
	void set_color(QColor color);
	void set_pen();
private:
	QPen pen;
};

#endif // PAINTER_H
