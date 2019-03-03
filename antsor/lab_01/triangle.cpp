#include "triangle.h"
#include "line.h"
#include "cmath"

Triangle::Triangle()
{
    points[0] = Point();
    points[1] = Point();
    points[2] = Point();
	min_height = LineSeg();
}

Triangle::Triangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
    points[0] = Point(x1, y1);
    points[1] = Point(x2, y2);
    points[2] = Point(x3, y3);
	
	if (isTriangle(this))
		setMinH();
	else
		min_height = LineSeg();
}

Triangle::Triangle(Point p1, Point p2, Point p3)
{
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
	
	if (isTriangle(this))
		setMinH();
	else
		min_height = LineSeg();
}

Point *Triangle::point(int i)
{
	if (i < 0 || i > 2)
		return nullptr;
	return &(points[i]);
}

void Triangle::setMinH()
{
	// прямые
	// hline - высоты, edgeline - стороны
	Line hline = Line(), edgeline = Line();
	// отрезки
	// h - текущая высота, hmin - минимальная высота
	LineSeg *h = nullptr, *hmin = nullptr;
	// hp - точка отрезка текущей высоты на стороне
	Point hp;
	
    for (int i = 0; i < 3; i++)
    {
		edgeline = Line(point((i + 1) % 3), point((i + 2) % 3));
		hline = Line(edgeline.b(), -edgeline.a(),
					 edgeline.a() * point(i)->y() -
					 edgeline.b() * point(i)->x());
        intersect(hline, edgeline, &hp);
		
		h = new LineSeg(point(i), &hp);
		
        if (!hmin || h->length() < hmin->length())
			hmin = h;
		else
			delete h;
	}
	
    min_height = *hmin;
}

LineSeg *Triangle::getMinHeight()
{
    return &min_height;
}

bool isTriangle(Point *p1, Point *p2, Point *p3)
{
	LineSeg a = LineSeg(p1, p2);
	LineSeg b = LineSeg(p1, p3);
	LineSeg c = LineSeg(p2, p3);
	return (a.length() + b.length() > c.length() &&
            a.length() + c.length() > b.length() &&
            b.length() + c.length() > a.length());
}

bool isTriangle(Triangle *tr)
{
	LineSeg a = LineSeg(tr->point(0), tr->point(1));
	LineSeg b = LineSeg(tr->point(0), tr->point(2));
	LineSeg c = LineSeg(tr->point(1), tr->point(2));
	
	return (a.length() + b.length() > c.length() &&
            a.length() + c.length() > b.length() &&
            b.length() + c.length() > a.length());
}


