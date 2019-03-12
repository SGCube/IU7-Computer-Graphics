#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "outline.h"

#define POINTS_N 4000

class Ellipse : public Outline
{
public:
	Ellipse(Point center, float a, float b);
	
private:
	Point line[POINTS_N];
};

#endif // ELLIPSE_H
