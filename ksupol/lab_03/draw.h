#ifndef DRAW_H
#define DRAW_H

#include <QGraphicsScene>

void set_colour(QColor *c, int bgc_col, int col);

void draw_library(int sX, int sY, int eX, int eY, QColor *c, QGraphicsScene *scene);

void draw_dda(int sX, int sY, int eX, int eY, QColor *cl, QGraphicsScene *scene);

void draw_real(int sX, int sY, int eX, int eY, QColor *c, QGraphicsScene *scene);

void draw_int(int sX, int sY, int eX, int eY, QColor *c, QGraphicsScene *scene);

void draw_step(int sX, int sY, int eX, int eY, QColor *c, QGraphicsScene *scene);

void draw_spectrum(QColor *c, int alg, float degr, QGraphicsScene *scene);

int my_round(double number);

#endif // DRAW_H
