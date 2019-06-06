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
	
	void setSource(const Point &value) { source = value; }
	void setPurpose(const Point &value) { purpose = value; }
	
	bool isHorizontal() { return source.y() == purpose.y(); }
	bool isVertical() { return source.x() == purpose.x(); }
	
	void swapPoints()
	{
		Point tmp = source;
		source = purpose;
		purpose = tmp;
	}
	
private:
	Point source, purpose;
};

#endif // LINESEG_H
