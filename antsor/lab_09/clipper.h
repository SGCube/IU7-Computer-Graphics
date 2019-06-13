#ifndef CLIPPER_H
#define CLIPPER_H

#include <vector>

#include "polygon.h"
#include "painter.h"
#include "pointdata.h"

class Clipper
{
public:
	Clipper(Polygon p) : clipper(p.toEdges()) {};
	
	void clip(std::vector<Polygon>& polygons, Painter& painter);
	void clipPolygon(Polygon& polygon, Painter& painter);
	bool clipByEdge(Polygon& polygon, LineSeg& edge);
	
private:
	std::vector<LineSeg> clipper;
	
	bool isVisible(Point& p, LineSeg& edge);
};

#endif // CLIPPER_H
