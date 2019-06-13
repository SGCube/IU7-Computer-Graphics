#include <cmath>

#include "clipper.h"
#include "lineseg.hpp"
#include "vector.hpp"

bool Clipper::clip(std::vector<Polygon> &polygons, Painter &painter)
{
	if (!isConvex())
		return false;
		
	for (size_t i = 0; i < polygons.size(); i++)
		clipPolygon(polygons[i], painter);
	return true;
}

void Clipper::clipPolygon(Polygon &polygon, Painter &painter)
{
	Polygon clipped = polygon;
	bool visible = true;
	for (size_t i = 0; i < clipper.size() && visible; i++)
		visible = clipByEdge(clipped, clipper[i]);
	
	if (visible)
	{
		for (size_t i = 0; i < clipped.size() - 1; i++)
			painter.drawClipped(clipped[i].x(), clipped[i].y(),
								clipped[i + 1].x(), clipped[i + 1].y());
		painter.drawClipped(clipped[clipped.size() - 1].x(),
				clipped[clipped.size() - 1].y(),
				clipped[0].x(), clipped[0].y());
	}
}

bool Clipper::clipByEdge(Polygon &polygon, LineSeg &clipEdge)
{
	Polygon result;
	result.clear();
	Point S, F, I;
	
	for (size_t j = 0; j < polygon.size(); j++)
	{
		if (j == 0)
			F = polygon[j];
		else
		{
			LineSeg sEdge(S, polygon[j]);
			if (isIntersect(S, polygon[j], clipEdge))
			{
				LineSeg::intersect(sEdge, clipEdge, I);
				result.add_point(I);
			}
		}
		
		S = polygon[j];
		if (isVisible(S, clipEdge))
			result.add_point(S);
	}
	
	if (result.size() == 0)
		return false;
	
	LineSeg lastEdge(S, F);
	if (isIntersect(S, F, clipEdge))
	{
		LineSeg::intersect(lastEdge, clipEdge, I);
		result.add_point(I);
	}
	
	polygon = result;
	return true;
}

bool Clipper::isVisible(Point &p, LineSeg &edge)
{
	Vector ps(p, edge.getP1());
	Vector dir(edge.getP1(), edge.getP2());
	
	Vector res = Vector::vectorMultiply(ps, dir);
	return res.z * direction >= 0;
}

bool Clipper::isIntersect(Point p1, Point p2, LineSeg &edge)
{
	bool vis1 = isVisible(p1, edge);
	bool vis2 = isVisible(p2, edge);
	return vis1 != vis2;
}

bool Clipper::isConvex()
{
	Vector a(clipper[0].getP1(), clipper[0].getP2());
	int sign = 0;
	for (size_t i = 1; i < clipper.size() - 1; i++)
	{
		Vector b(clipper[i].getP1(), clipper[i].getP2());
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
