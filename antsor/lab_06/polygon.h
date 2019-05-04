#ifndef POLYGON_H
#define POLYGON_H

#include <vector>

#include "point.h"
#include "edge.h"

class Polygon
{
public:
	Polygon();
	~Polygon();
	void add_point(Point);
	void clear();
	int number_of_vertexes();
	Point first_point();
	Point last_point();
	Point operator[](int i);
	
	static std::vector<Edge> set_to_edges(std::vector<Polygon> set);
private:
	std::vector<Point> vertexes;
};

#endif // POLYGON_H
