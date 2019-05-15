#ifndef PAINTER_H
#define PAINTER_H

#include <QPainter>
#include <vector>
#include "point.h"
#include "polygon.h"

class Painter : public QPainter
{
public:
	Painter();
	void set_color_edge(QColor color);
	void set_color_fill(QColor color);
	void set_color_bg(QColor color);
	
	void set_fill();
	void set_bg();
	void set_edge();
	
	bool is_bg(QColor color);
	bool is_fill(QColor color);
	bool is_edge(QColor color);
	
	void draw_line(Point p1, Point p2);
	void draw_polygons(QImage *img, std::vector<Polygon> &set);
	
private:
	QPen pen;
	QColor color_fill;
	QColor color_bg;
	QColor color_edge;
};

#endif // PAINTER_H
