#ifndef LINESEG_H
#define LINESEG_H

#include "outline.h"

class LineSeg : public Outline
{
public:
	LineSeg(Point p1, Point p2);
	
	double length();
	
private:
	Point vertex[2];
};

#endif // LINESEG_H
