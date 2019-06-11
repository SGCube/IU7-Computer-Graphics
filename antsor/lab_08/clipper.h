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
	Clipper(Polygon p);
	
	void clip(std::vector<LineSeg>& lines, Painter& painter);
	//void clipLineSeg(LineSeg& line, Painter& painter);
	
private:
	enum Visibility
	{
		INVISIBLE = -1,
		PART_VISIBLE = 0,
		VISIBLE = 1
	};
	
	enum PosState
	{
		VERTICAL = -1,
		COMMON = 0,
		HORIZONTAL = 1
	};
	
	//Visibility isVisible(Point p1, Point p2);
	
	Polygon polygon;
};

#endif // CLIPPER_H
