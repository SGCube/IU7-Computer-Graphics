#ifndef CLIPPER_H
#define CLIPPER_H

#include <vector>

#include "point.h"
#include "lineseg.hpp"
#include "polygon.h"
#include "painter.h"
#include "vector.hpp"

class Clipper
{
public:
	Clipper(Polygon p) : edges(p.toEdges()), direction(-1) {}
	
	bool clip(std::vector<LineSeg>& lines, Painter& painter);
	void clipLineSeg(LineSeg& line, Painter& painter);
	
private:
	std::vector<LineSeg> edges;
	int direction;
	
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
