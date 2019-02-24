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
	QPoint lt_corner();
	QPoint rb_corner();
};

bool isTriangle(QPointF p1, QPointF p2, QPointF p3);

#endif // TRIANGLE_H
