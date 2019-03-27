#ifndef DRAW_H
#define DRAW_H

#include <QGraphicsScene>

void draw_library(float sX, float sY, float eX, float eY, int col, int bgc_col, QGraphicsScene *scene);

void draw_cda(float sX, float sY, float eX, float eY, int col, int bgc_col, QGraphicsScene *scene, QPixmap px);

void draw_real(float sX, float sY, float eX, float eY, int col, int bgc_col, QGraphicsScene *scene);

void draw_int(float sX, float sY, float eX, float eY, int col, int bgc_col, QGraphicsScene *scene);

void draw_step(float sX, float sY, float eX, float eY, int col, int bgc_col, QGraphicsScene *scene);

#endif // DRAW_H
