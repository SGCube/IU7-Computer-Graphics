#ifndef LINESEG_H
#define LINESEG_H

#include <cmath>

#include "point.h"

class LineSeg
{
public:
	LineSeg(int sx, int sy, int px, int py) : p1(sx, sy), p2(px, py) {}
	LineSeg(Point s, Point p) : p1(s), p2(p) {}
	
	Point& getP1() { return p1; }
	Point& getP2() { return p2; }
	
	void setP1(const Point &value) { p1 = value; }
	void setP2(const Point &value) { p2 = value; }
	
	bool isHorizontal() { return p1.y() == p2.y(); }
	bool isVertical() { return p1.x() == p2.x(); }
	
	void swapPoints()
	{
		Point tmp = p1;
		p1 = p2;
		p2 = tmp;
	}
	
	Point getParam(double t)
	{
		int x = p1.x() + round((p2.x() - p1.x()) * t);
		int y = p1.y() + round((p2.y() - p1.y()) * t);
		return Point(x, y);
	}
	
	static Point intersect(LineSeg p, LineSeg q)
	{
		Point& p1 = p.getP1(), p2 = p.getP2();
		Point& q1 = q.getP1(), q2 = q.getP2();
		
		double dxp = p2.x() - p1.x();
		double dyp = p2.y() - p1.y();
		double dxq = q2.x() - q1.x();
		double dyq = q2.y() - q2.y();
		double mq = dxq / dyq;
		double t = (q1.x() - p1.x() + mq * (p1.y() - q1.y())) / (dxp - mq * dyp);
		return p.getParam(t);
	}
	
private:
	Point p1, p2;
};

#endif // LINESEG_H
