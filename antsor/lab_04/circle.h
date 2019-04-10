#ifndef CIRCLE_H
#define CIRCLE_H

#include <QPainter>
#include "point.h"

void draw_circle_canon(QPainter *painter, Point pc, double r);

void draw_circle_param(QPainter *painter, Point pc, double r);

void draw_circle_bresem(QPainter *painter, Point pc, double r);

//void draw_circle_midpoint(QPainter *painter, Point pc, double r);

void draw_circle_lib(QPainter *painter, Point pc, double r);

#endif // CIRCLE_H
