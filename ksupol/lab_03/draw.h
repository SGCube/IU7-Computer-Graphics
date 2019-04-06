#ifndef DRAW_H
#define DRAW_H

#include <QGraphicsScene>

void draw_library(float sX, float sY, float eX, float eY, int col, int bgc_col, QGraphicsScene *scene);

void draw_dda(float sX, float sY, float eX, float eY, int col, int bgc_col, QGraphicsScene *scene);

void draw_real(float sX, float sY, float eX, float eY, int col, int bgc_col, QGraphicsScene *scene);

void draw_int(float sX, float sY, float eX, float eY, int col, int bgc_col, QGraphicsScene *scene);

void draw_step(float sX, float sY, float eX, float eY, int col, int bgc_col, QGraphicsScene *scene);

void draw_spectrum(int col, int bgc_col, int alg, float degr, QGraphicsScene *scene);

int my_round(double number);

#endif // DRAW_H
