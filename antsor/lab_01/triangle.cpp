#include "triangle.h"
#include "cmath"

Triangle::Triangle()
{
    points[0] = QPointF(0, 0);
    points[1] = QPointF(0, 0);
    points[2] = QPointF(0, 0);
}

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

QVector2D getMinHeight(float *p1, float *p2, float *p3, int *hvertex)
{
	QPointF points[3];
	points[0].setX(p1[0]);
	points[0].setY(p1[1]);
	points[1].setX(p2[0]);
	points[1].setY(p2[1]);
	points[2].setX(p3[0]);
	points[2].setY(p3[1]);
	
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


Triangle solve(float **plist, int n, float *hmin)
{
	if (!plist || n < 3)
		return Triangle();
	
	float h = -1;
	*hmin = -1;
	int i1 = 0, i2 = 1, i3 = 2, hvertex = 0;
	for (int i = 0; i < n - 2; i++)
		for (int j = i + 1; j < n - 1; j++)
			for (int k = j + 1; k < n; k++)
			{
				if (isTriangle(plist[i1][0], plist[i1][1],
							   plist[i2][0], plist[i2][1],
							   plist[i3][0], plist[i3][1]))
				{
					h = getMinHeight(plist[i], plist[j],
									 plist[k], &hvertex).length();
					if (*hmin == -1 || h < *hmin)
					{
						i1 = i;
						i2 = j;
						i3 = k;
						*hmin = h;
					}
				}
			}
	
	return Triangle(plist[i1][0], plist[i1][1],
			plist[i2][0], plist[i2][1],
			plist[i3][0], plist[i3][1]);
}
