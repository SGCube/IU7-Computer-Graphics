#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "outline.h"

#define POINTS_N 1000

class Ellipse : public Outline
{
public:
	Ellipse();
	Ellipse(Point p, float a, float b);
	
	Point *center();
	void setCenter(Point p);
	
	float a();
	float b();
	void setA(float a);
	void setB(float b);
	
private:
	Point pc;
	float ra, rb;
	Point line[4 * POINTS_N];
};

#endif // ELLIPSE_H
