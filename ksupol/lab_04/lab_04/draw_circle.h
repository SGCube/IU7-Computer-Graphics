#ifndef DRAW_H
#define DRAW_H

#include <QGraphicsScene>
#include <QColor>

void set_colour(int bgc_col, int col, QColor *c);

void draw_library(double x, double y, double rad, QColor *c, QGraphicsScene *scene);

void draw_kanon(double x, double y, double rad, QColor *c, QGraphicsScene *scene);

void draw_param(double x, double y, double r, QColor *c, QGraphicsScene *scene);

void draw_bres(double x, double y, double r, QColor *c, QGraphicsScene *scene);

void draw_mid(double xx, double yy, double r, QColor *c, QGraphicsScene *scene);

void color_pix(int x0, int y0, int x, int y, QPen pen, QGraphicsScene *scene);

void draw_cir_spectr(int s_r, int e_r, int k, QColor *c, QGraphicsScene *scene, int alg);

#endif // DRAW_H
