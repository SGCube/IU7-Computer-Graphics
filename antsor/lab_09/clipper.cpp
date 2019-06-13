#include <cmath>

#include "clipper.h"
#include "lineseg.hpp"
#include "vector.hpp"

void Clipper::clip(std::vector<Polygon> &polygons, Painter &painter)
{
	for (size_t i = 0; i < polygons.size(); i++)
		clipPolygon(polygons[i], painter);
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
				clipped[clipped.size() - 1].y(), clipped[0].x(), clipped[0].y());
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
			if (LineSeg::intersect(sEdge, clipEdge, I))
				result.add_point(I);
		}
		
		S = polygon[j];
		if (isVisible(S, clipEdge))
			result.add_point(S);
	}
	
	if (result.size() == 0)
		return false;
	
	LineSeg lastEdge(S, F);
	if (LineSeg::intersect(lastEdge, clipEdge, I))
		result.add_point(I);
	
	polygon = result;
	return true;
}

bool Clipper::isVisible(Point &p, LineSeg &edge)
{
	Vector ps(p, edge.getP1());
	Vector dir(edge.getP1(), edge.getP2());
	
	Vector res = Vector::vectorMultiply(ps, dir);
	return res.z >= 0;
}
