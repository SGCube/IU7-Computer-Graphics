#include <QGraphicsView>
#include <QPointF>
#include <QVector2D>

#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle
{
public:
	QPointF points[3];
	
	Triangle();
    Triangle(float x1, float y1, float x2, float y2, float x3, float y3);
    Triangle(QPointF p1, QPointF p2, QPointF p3);
	QVector2D getMinHeight(QPointF *hvertex);
};

bool isTriangle(QPointF p1, QPointF p2, QPointF p3);

bool solve(QPointF *plist, int n, Triangle *tr, QVector2D *h, QPointF *hvertex);

#endif // TRIANGLE_H
