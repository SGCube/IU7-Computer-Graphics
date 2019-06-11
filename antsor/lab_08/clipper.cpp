#include <cmath>

#include "clipper.h"
#include "vector.hpp"

void Clipper::clip(std::vector<LineSeg>& lines, Painter& painter)
{
	for (size_t i = 0; i < lines.size(); i++)
		clipLineSeg(lines[i], painter);
}

void Clipper::clipLineSeg(LineSeg& line, Painter& painter)
{
	Point p1 = line.getP1();
	Point p2 = line.getP2();
	
	if (!isConvex())
		return;
	
	bool toFinish = false;
	
	int tBottom = 0, tTop = 1;
	Vector d(p1, p2);
	
	for (size_t i = 0; i < edges.size() && !toFinish; i++)
	{
		LineSeg edge = edges[i];
		
		Vector normal;
		Vector tmp(edge.getP1(), edge.getP2());
		if (direction == 1)
			normal = Vector(-tmp.y, tmp.x);
		else
			normal = Vector(tmp.y, -tmp.x);
		
		
		Vector w(p1, edge.getP1());
		double dScalar = Vector::scalarMultiply(normal, d);
		double wScalar = Vector::scalarMultiply(w, normal);
		
		
		if (dScalar == 0)
		{
			if (wScalar < 0)
				toFinish = true;
		}
		else
		{
			double t = -double(wScalar)/dScalar;
			if (dScalar > 0)
			{
				if (t > 1)
					toFinish = true;
				else
				{
					if (t > tBottom)
						tBottom = t;
				}
			}
			else
			{
				if (t < 0)
					toFinish = true;
				else
				{
					if (t < tTop)
						tTop = t;
				}
			}
		}
	}
	
	if (!toFinish && tBottom <= tTop)
	{
		Point pp1 = line.getParam(tBottom);
		Point pp2 = line.getParam(tTop);
		painter.drawClipped(pp1.x(), pp1.y(), pp2.x(), pp2.y());
	}
}

bool Clipper::isConvex()
{
	Vector a(edges[0].getP1(), edges[0].getP2());
	int sign = 0;
	for (size_t i = 1; i < edges.size() - 1; i++)
	{
		Vector b(edges[i].getP1(), edges[i].getP2());
		Vector n = Vector::vectorMultiply(a, b);
		if (sign == 0)
			sign = signFunc(n.z);
		if (n.z != 0 && sign != signFunc(n.z))
		{
			direction = 0;
			return false;
		}
		a = b;
	}
	direction = sign;
	return true;
}
