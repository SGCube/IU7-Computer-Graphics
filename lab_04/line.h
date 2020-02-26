#ifndef DRAW_H
#define DRAW_H

#include <QPainter>
#include "point.h"

void draw_line_dda(QPainter *painter, Point p1, Point p2);

void draw_line_bres_real(QPainter *painter, Point p1, Point p2);

void draw_line_bres_int(QPainter *painter, Point p1, Point p2);

void draw_line_bres_aa(QPainter *painter, Point p1, Point p2);

#endif // DRAW_H
