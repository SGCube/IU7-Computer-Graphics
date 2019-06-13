#ifndef POLYGON_H
#define POLYGON_H

#include <vector>

#include "point.h"
#include "lineseg.hpp"

class Polygon
{
public:
	Polygon() {}
	Polygon(const Polygon& p);
	Polygon(Polygon&& p);
	~Polygon();
	
	Polygon& operator=(const Polygon& p);
	Polygon& operator=(Polygon&& p);
	
	void add_point(Point);
	void clear();
	size_t size();
	Point first_point();
	Point last_point();
	Point operator[](int i);
	
	
	std::vector<LineSeg> toEdges();
private:
	std::vector<Point> vertexes;
};

#endif // POLYGON_H
