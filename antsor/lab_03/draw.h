#ifndef DRAW_H
#define DRAW_H

//#include <QPainter>
#include <QImage>

#include "point.h"

void draw_line_dda(QImage *img, Point p1, Point p2, QColor color);

void draw_line_bres_real(QImage *img, Point p1, Point p2, QColor color);

void draw_line_bres_int(QImage *img, Point p1, Point p2, QColor color);

void draw_line_bres_aa(QImage *img, Point p1, Point p2, QColor color);

#endif // DRAW_H
