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
	int direction;
	
	bool isVisible(Point& p, LineSeg& edge);
	bool isConvex();
	
	static int signFunc(int x)
	{
		if (x > 0)
			return 1;
		if (x < 0)
			return -1;
		return 0;
	}
	
};

#endif // CLIPPER_H
