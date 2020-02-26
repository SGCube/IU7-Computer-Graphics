#ifndef ARC_H
#define ARC_H

#include "ellipse.h"

class Arc : public Outline
{
public:
	Arc(Point p = Point(0, 0), double a = 100, double b = 100, int angle = 180);
private:
	Point line[POINTS_N];
};

#endif // ARC_H
