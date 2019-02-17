#include <QPointF>
#include <QVector2D>

#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle
{
public:
    Triangle(float x1, float y1, float x2, float y2, float x3, float y3);
    Triangle(QPointF p1, QPointF p2, QPointF p3);
	QPointF points[3];
private:
	Triangle getMinHeight(int *hvertex);
};

bool isTriangle(float x1, float y1, float x2, float y2, float x3, float y3);

QVector2D getMinHeight(float *p1, float *p2, float *p3, int *hvertex);

Triangle solve(float **plist, int n);

#endif // TRIANGLE_H
