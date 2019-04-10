#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <QPainter>
#include "point.h"

void draw_ellipse_canon(QPainter *painter, Point pc, double a, double b);

void draw_ellipse_param(QPainter *painter, Point pc, double a, double b);

void draw_ellipse_bresem(QPainter *painter, Point pc, double a, double b);

void draw_ellipse_midpoint(QPainter *painter, Point pc, double a, double b);

void draw_ellipse_lib(QPainter *painter, Point pc, double a, double b);

#endif // ELLIPSE_H
