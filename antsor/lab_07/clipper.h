#ifndef CLIPPER_H
#define CLIPPER_H

#include <vector>

#include "point.h"
#include "lineseg.hpp"
#include "painter.h"

class Clipper
{
public:
	Clipper(int x1, int y1, int x2, int y2);
	
	void clip(std::vector<LineSeg>& lines, Painter& painter);
	void clipLineSeg(LineSeg& line, Painter& painter);
	
private:
	struct
	{
		unsigned outOfLeft = 1;
		unsigned outOfRight = 2;
		unsigned outOfTop = 4;
		unsigned outOfBottom = 8;
		
		unsigned outOfNone = 0;
		unsigned outOfEverything = 15;
	} codeMasks;
	
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
	
	unsigned getCode(Point& p);
	Visibility isVisible(Point p1, Point p2);
	
	int left;
	int right;
	int top;
	int bottom;
};

#endif // CLIPPER_H
