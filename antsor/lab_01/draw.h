#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <QPainter>

#include "triangle.h"
	
void drawTriangle(QGraphicsScene *scene, Triangle *tr);

void drawPoints(QGraphicsScene *scene, QPointF *plist, int n);

void draw(QGraphicsScene *scene, Triangle *tr, QPointF *plist, int n);


#endif // DRAW_H
