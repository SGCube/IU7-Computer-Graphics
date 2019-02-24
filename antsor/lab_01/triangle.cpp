#include "triangle.h"
#include "line.h"
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

QVector2D Triangle::getMinHeight(QPointF *hvertex)
{
	// h - длина текущей высоты, hmin - длина минимальной высоты
	float h = -1, hmin = -1;
	// hline - высота, edge - сторона
	Line hline, edge;	
	// hp - точка отрезка текущей высоты на стороне
	// hpmin - точка отрезка минимальной высоты на стороне
	QPointF hp, hpmin;
	
    for (int i = 0; i < 3; i++)
    {
		edge = Line(QPointF(points[(i + 1) % 3]),
				QPointF(points[(i + 2) % 3]));
		hline = Line(edge.b, -edge.a,
					 edge.a * points[i].y() - edge.b * points[i].x());
        intersect(hline, edge, &hp);
		
        h = sqrt(pow(hp.x() - points[i].x(), 2) + 
				 pow(hp.y() - points[i].y(), 2));
		
        if (hmin == -1 || h < hmin)
        {
            hpmin = hp;
			hmin = h;
            *hvertex = points[i];
        }
	}
	
    return QVector2D(hpmin.x() - hvertex->x(),
					 hpmin.y() - hvertex->y());
}

QPoint Triangle::lt_corner()
{
	float min_x = fmin(fmin(points[0].x(), points[1].x()), points[2].x());
	float min_y = fmin(fmin(points[0].y(), points[1].y()), points[2].y());
	
	int cx = (int) ceil(min_x);
	int cy = (int) ceil(min_y);
	
	return QPoint(cx, cy);
}

QPoint Triangle::rb_corner()
{
	float max_x = fmax(fmin(points[0].x(), points[1].x()), points[2].x());
	float max_y = fmax(fmin(points[0].y(), points[1].y()), points[2].y());
	
	int cx = (int) floor(max_x);
	int cy = (int) floor(max_y);
	
	return QPoint(cx, cy);
}

bool isTriangle(QPointF p1, QPointF p2, QPointF p3)
{
	QVector2D a = QVector2D(p2.x() - p1.x(), p2.y() - p1.y());
	QVector2D b = QVector2D(p3.x() - p1.x(), p3.y() - p1.y());
	QVector2D c = QVector2D(p3.x() - p2.x(), p3.y() - p2.y());
	return (a.length() + b.length() > c.length() &&
            a.length() + c.length() > b.length() &&
            b.length() + c.length() > a.length());
}


bool solve(QPointF *plist, int n, Triangle *tr, QVector2D *h, QPointF *hvertex)
{
	if (!plist || n < 3)
		return false;
	
	// h - высота минимальной длины текущего треугольника
	QVector2D hcur;
	// hcurv - вершина высоты текущего треугольника
	QPointF hcurv;
	// trcur - текущий рассматриваемый треугольник
	Triangle trcur;
	// found - найдено ли хотя бы одно решение
	bool found = false;
	
	for (int i = 0; i < n - 2; i++)
		for (int j = i + 1; j < n - 1; j++)
			for (int k = j + 1; k < n; k++)
			{
				if (isTriangle(plist[i], plist[j], plist[k]))
				{
					trcur = Triangle(plist[i], plist[j], plist[k]);
					hcur = trcur.getMinHeight(&hcurv);
					if (!found || hcur.length() < h->length())
					{
						*tr = trcur;
						*h = hcur;
						*hvertex = hcurv;
						found = true;
					}
				}
			}
	
	return found;
}
