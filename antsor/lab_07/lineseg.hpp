#ifndef LINESEG_H
#define LINESEG_H

#include "point.h"

class LineSeg
{
public:
	LineSeg(int sx, int sy, int px, int py) : source(sx, sy), purpose(px, py) {}
	LineSeg(Point s, Point p) : source(s), purpose(p) {}
	
	Point& getSource() { return source; }
	Point& getPurpose() { return purpose; }
	
	bool isHorizontal() { return source.y() == purpose.y(); }
	bool isVertical() { return source.x() == purpose.x(); }
	
private:
	Point source, purpose;
};

#endif // LINESEG_H
