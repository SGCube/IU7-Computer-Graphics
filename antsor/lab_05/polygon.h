#ifndef POLYGON_H
#define POLYGON_H

#include <point.h>
#include <vector>


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
private:
	std::vector<Point> vertexes;
};

#endif // POLYGON_H
