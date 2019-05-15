#ifndef FILL_H
#define FILL_H

#include <QImage>
#include <QGraphicsScene>
#include <vector>

#include "painter.h"
#include "edge.h"
#include "polygon.h"

struct ColorSet
{
	QColor color_edge;
	QColor color_fill;
	QColor color_bg;
	
	ColorSet(QColor, QColor, QColor);
};

Point lt_corner(std::vector<Polygon> set);

Point rd_corner(std::vector<Polygon> set);

void fill(QImage *img, ColorSet color_set, QGraphicsScene *scene, Point span,
		  int delay = 0);

#endif // FILL_H
