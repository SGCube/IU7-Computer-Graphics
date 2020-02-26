#ifndef EDGE_H
#define EDGE_H

#include "point.h"

class Edge
{
public:
	Edge();
	Edge(float x1, float y1, float x2, float y2);
	Edge(Point p1, Point p2);
	
	Point *p1();
	Point *p2();
	
	double length();
	bool is_horizontal();
	bool is_vertical();
	
private:
	Point end1, end2;
};

#endif // EDGE_H
