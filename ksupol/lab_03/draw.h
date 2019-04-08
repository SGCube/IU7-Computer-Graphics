#ifndef DRAW_H
#define DRAW_H

#include <QGraphicsScene>

void set_colour(QColor *c, int bgc_col, int col);

void draw_library(float sX, float sY, float eX, float eY, QColor *c, QGraphicsScene *scene);

void draw_dda(float sX, float sY, float eX, float eY, QColor *cl, QGraphicsScene *scene);

void draw_real(float sX, float sY, float eX, float eY, QColor *c, QGraphicsScene *scene);

void draw_int(float sX, float sY, float eX, float eY, QColor *c, QGraphicsScene *scene);

void draw_step(float sX, float sY, float eX, float eY, QColor *c, QGraphicsScene *scene);

void draw_spectrum(QColor *c, int alg, float degr, QGraphicsScene *scene);

int my_round(double number);

#endif // DRAW_H
