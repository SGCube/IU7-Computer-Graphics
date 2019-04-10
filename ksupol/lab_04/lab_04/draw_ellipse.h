#ifndef DRAW_ELLIPSE_H
#define DRAW_ELLIPSE_H

#include <QColor>
#include <QPen>
#include <QGraphicsScene>

void draw_el_library(double x, double y, double a, double b, QColor *c, QGraphicsScene *scene);

void draw_el_kanon(double x, double y, double a, double b, QColor *c, QGraphicsScene *scene);

void draw_el_param(double x, double y, double a, double b, QColor *c, QGraphicsScene *scene);

void draw_el_mid(double x, double y, double a, double b, QColor *c, QGraphicsScene *scene);

void draw_el_bres(double x, double y, double a, double b, QColor *c, QGraphicsScene *scene);

#endif // DRAW_ELLIPSE_H
