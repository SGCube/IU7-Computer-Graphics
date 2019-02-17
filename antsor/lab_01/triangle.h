#include <QPointF>
#include <QVector2D>

#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle
{
public:
    Triangle(float x1, float y1, float x2, float y2, float x3, float y3);
    Triangle(QPointF p1, QPointF p2, QPointF p3);
private:
    QPointF points[3];
    QVector2D getMinHeight(int *hvertex);
};

bool isTriangle(float x1, float y1, float x2, float y2, float x3, float y3);

Triangle solve(float **plist, int n);

#endif // TRIANGLE_H
