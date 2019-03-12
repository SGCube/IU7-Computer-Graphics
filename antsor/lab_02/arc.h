#ifndef ARC_H
#define ARC_H

#include "ellipse.h"

class Arc : public Ellipse
{
public:
	Arc(Point p, float a, float b);
private:
	int angle;
};

#endif // ARC_H
