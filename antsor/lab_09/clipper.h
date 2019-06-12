#ifndef CLIPPER_H
#define CLIPPER_H

#include <vector>

#include "point.h"
#include "lineseg.hpp"
#include "polygon.h"
#include "painter.h"

class Clipper
{
public:
	Clipper(std::vector<Polygon> p) : clippers(p), direction(-1) {}
	
	void clip(std::vector<Polygon>& polygons, Painter& painter);
	
private:
	std::vector<Polygon> clippers;
	int direction;
	
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
