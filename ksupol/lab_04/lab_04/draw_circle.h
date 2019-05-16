#ifndef DRAW_H
#define DRAW_H

#include <QGraphicsScene>
#include <QColor>

void set_colour(int bgc_col, int col, QColor *c);

void draw_library(int x, int y, int rad, QColor *c, QGraphicsScene *scene);

void draw_kanon(int x, int y, int rad, QColor *c, QGraphicsScene *scene);

void draw_param(int x, int y, int r, QColor *c, QGraphicsScene *scene);

void draw_bres(int xx, int yy, int r, QColor *c, QGraphicsScene *scene);

void draw_mid(int xx, int yy, int r, QColor *c, QGraphicsScene *scene);

void color_pix_cir(int x0, int y0, int x, int y, QPen pen, QGraphicsScene *scene);

void draw_cir_spectr(int x, int y, int s_r, int e_r, int k, QColor *c, QGraphicsScene *scene, int alg);

#endif // DRAW_H
