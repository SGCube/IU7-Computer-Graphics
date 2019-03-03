#include "triangle.h"
#include "line.h"
#include "cmath"

Triangle::Triangle()
{
    points[0] = Point(0, 0);
    points[1] = Point(0, 0);
    points[2] = Point(0, 0);
}

Triangle::Triangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
    points[0] = Point(x1, y1);
    points[1] = Point(x2, y2);
    points[2] = Point(x3, y3);
}

Triangle::Triangle(Point p1, Point p2, Point p3)
{
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
}

Point *Triangle::point(int i)
{
	if (i < 0 || i > 2)
		return nullptr;
	return points[i];
}

void Triangle::setMinH()
{
	// прямые
	// hline - высоты, edgeline - стороны
	Line hline = Line(), edgeline = Line();
	// отрезки
	// h - текущая высота, hmin - минимальная высота
	LineSeg *h = LineSeg(), *hmin = nullptr;
	// hp - точка отрезка текущей высоты на стороне
	Point hp;
	
    for (int i = 0; i < 3; i++)
    {
		edgeline = Line(point((i + 1) % 3), point((i + 2) % 3));
		hline = Line(edgeline.b(), -edgeline.a(),
					 edgeline.a() * point(i)->y() -
					 edgeline.b() * point(i)->x());
        intersect(hline, edgeline, &hp);
		
		h->LineSeg(point(i), hp);
		
        if (!hmin || h->length() < hmin->length())
			hmin = h;
	}
	
    min_height = *hmin;
}

LineSeg *Triangle::getMinHeight()
{
    return &min_height;
}

QPoint Triangle::lt_corner()
{
	float min_x = fmin(fmin(point(0)->x(), point(0)->x()), point(2)->x());
	float min_y = fmin(fmin(point(0)->y(), point(1)->y()), point(2)->y());
	
	LineSeg *h = getMinHeight(&hv);
	
	min_x = fmin(h->p2()->x(), min_x);
	min_y = fmin(h->p2()->y(), min_y);
	
	int cx = (int) floor(min_x);
	int cy = (int) floor(min_y);
	
	return QPoint(cx, cy);
}

QPoint Triangle::rb_corner()
{
	float max_x = fmax(fmax(point(0)->x(), point(0)->x()), point(2)->x());
	float max_y = fmax(fmax(point(0)->y(), point(1)->y()), point(2)->y());
	
	LineSeg *h = getMinHeight(&hv);
	
	max_x = fmax(h->p2()->x(), max_x);
	max_y = fmax(h->p2()->y(), max_y);
	
	int cx = (int) ceil(max_x);
	int cy = (int) ceil(max_y);
	
	return QPoint(cx, cy);
}

bool isTriangle(Point p1, Point p2, Point p3)
{
	LineSeg a = LineSeg(p2.x() - p1.x(), p2.y() - p1.y());
	LineSeg b = LineSeg(p3.x() - p1.x(), p3.y() - p1.y());
	LineSeg c = LineSeg(p3.x() - p2.x(), p3.y() - p2.y());
	return (a.length() + b.length() > c.length() &&
            a.length() + c.length() > b.length() &&
            b.length() + c.length() > a.length());
}


