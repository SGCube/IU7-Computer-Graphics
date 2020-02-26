#include <cmath>

#include "clipper.h"
#include "vector.hpp"

bool Clipper::clip(std::vector<LineSeg>& lines, Painter& painter)
{
	if (!isConvex())
		return false;
	
	for (size_t i = 0; i < lines.size(); i++)
		clipLineSeg(lines[i], painter);
	return true;
}

void Clipper::clipLineSeg(LineSeg& line, Painter& painter)
{
	Point p1 = line.getP1();
	Point p2 = line.getP2();
	
	double t1 = 0, t2 = 1;
	Vector d(p1, p2);
	
	for (size_t i = 0; i < edges.size(); i++)
	{
		LineSeg edge = edges[i];
		Vector edgeVector(edge.getP1(), edge.getP2());
		
		Vector n = Vector::normal(edgeVector, direction);
		Vector w(edge.getP1(), p1);
		
		double dScalar = Vector::scalarMultiply(n, d);
		double wScalar = Vector::scalarMultiply(n, w);
		
		if (dScalar == 0)
		{
			if (wScalar < 0)
				return;
		}
		else
		{
			double t = -double(wScalar)/double(dScalar);
			if (dScalar > 0)
			{
				if (t > 1)
					return;
				
				if (t > t1)
					t1 = t;
			}
			else
			{
				if (t < 0)
					return;
				
				if (t < t2)
					t2 = t;
			}
		}
	}
	
	if (t1 <= t2)
	{
		Point pp1 = line.getParam(t1);
		Point pp2 = line.getParam(t2);
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
