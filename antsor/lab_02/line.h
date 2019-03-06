#ifndef LINE_H
#define LINE_H

#include "point.h"
#include "lineseg.h"

class Line
{
public:
	Line();
	Line(float a, float b, float c);
	Line(Point *p1, Point *p2);
	Line(LineSeg seg);
	
	float y(float x, bool *nz);
	float x(float y, bool *nz);
	
	float a();
	float b();
	float c();
	
	void setA(float k);
	void setB(float k);
	void setC(float k);
	
private:
	float ka, kb, kc;
};

bool intersect(Line l1, Line l2, Point *p);

#endif // LINE_H
