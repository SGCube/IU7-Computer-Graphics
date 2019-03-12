#ifndef ARC_H
#define ARC_H

#include "ellipse.h"

class Arc : public Ellipse
{
public:
	Arc(Point p = Point(0, 0), float a = 100, float b = 100, int ang = 180);
private:
	int angle;
};

#endif // ARC_H
