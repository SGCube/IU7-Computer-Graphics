#include "triangle.h"
#include "cmath"

Triangle::Triangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
    points[0] = QPointF(x1, y1);
    points[1] = QPointF(x2, y2);
    points[2] = QPointF(x3, y3);
}

Triangle::Triangle(QPointF p1, QPointF p2, QPointF p3)
{
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
}

QVector2D Triangle::getMinHeight(int *hvertex)
{
    float x, y, xm, ym, xp, yp;
    float h = -1, hm = -1;
    for (int i = 0; i < 3; i++)
    {
        x = points[i].x() + points[(i + 2) % 3].y() - points[(i + 1) % 3].y();
        y = points[i].y() - points[(i + 2) % 3].x() + points[(i + 1) % 3].x();
        h = sqrt(x * x + y * y);
        if (hm == -1 || h < hm)
        {
            hm = h;
            xm = x;
            ym = y;
            *hvertex = i;
            xp = points[i].x();
            yp = points[i].y();
        }
    }
    return QVector2D(QPointF(xm - xp, ym - yp));
}


bool isTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
	QVector2D a = QVector2D(QPointF(x2 - x1, y2 - y1));
	QVector2D b = QVector2D(QPointF(x3 - x1, y3 - y1));
	QVector2D c = QVector2D(QPointF(x3 - x2, y3 - y2));
	return (a.length() + b.length() > c.length() &&
            a.length() + c.length() > b.length() &&
            b.length() + c.length() > a.length());
}


Triangle solve(float **plist, int n)
{
	if (!plist || n < 3)
		return NULL;
	
	for (int i = 0; i < n - 2; i++)
		for (int j = i + 1; j < n - 2; j++)
			for (int k = j + 1; k < n - 2; k++)
			{
				
			}
}
