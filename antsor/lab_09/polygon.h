#ifndef POLYGON_H
#define POLYGON_H

#include <list>

#include "point.h"
#include "lineseg.hpp"

class Polygon
{
public:
	Polygon() {}
	~Polygon();
	void add_point(Point);
	void clear();
	int number_of_vertexes();
	Point first_point();
	Point last_point();
	Point operator[](int i);
	
	std::list<LineSeg> toEdges();
private:
	std::list<Point> vertexes;
};

#endif // POLYGON_H
