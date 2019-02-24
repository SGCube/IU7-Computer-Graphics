#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <QPainter>

#include "triangle.h"

#define PAD_X 50
#define PAD_Y 50

#define VIEW_W 600
#define VIEW_H 500
	
void drawTriangle(QGraphicsScene *scene, Triangle *tr, float kdraw,
				  QPoint center);

void drawPoints(QGraphicsScene *scene, QPointF *plist, int n, float kdraw,
				QPoint center);

void draw(QGraphicsScene *scene, Triangle *tr, QPointF *plist, int n);


#endif // DRAW_H
