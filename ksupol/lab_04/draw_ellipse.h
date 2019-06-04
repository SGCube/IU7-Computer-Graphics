#ifndef DRAW_ELLIPSE_H
#define DRAW_ELLIPSE_H

#include <QColor>
#include <QPen>
#include <QGraphicsScene>

void draw_el_library(int x, int y, int a, int b, QColor *c, QGraphicsScene *scene);

void draw_el_kanon(int x, int y, float a, float b, QColor *c, QGraphicsScene *scene);

void draw_el_param(int x, int y, float a, float b, QColor *c, QGraphicsScene *scene);

void draw_el_mid(int x, int y, int a, int b, QColor *c, QGraphicsScene *scene);

void draw_el_bres(int x, int y, int a, int b, QColor *c, QGraphicsScene *scene);

void draw_el_spectr(int x, int y, int s_a, int e_a, int s_b, int k, QColor *c, QGraphicsScene *scene, int alg);

void color_pixel(int x0, int y0, int x, int y, QPen pen, QGraphicsScene *scene);
#endif // DRAW_ELLIPSE_H
