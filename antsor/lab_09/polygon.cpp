#include "polygon.h"

Polygon::~Polygon()
{
	vertexes.clear();
}


void Polygon::add_point(Point p)
{
	vertexes.push_back(p);
}

void Polygon::clear()
{
	vertexes.clear();
}

int Polygon::number_of_vertexes()
{
	return vertexes.size();
}

Point Polygon::first_point()
{
	return vertexes.front();
}

Point Polygon::last_point()
{
	return vertexes.back();
}

Point Polygon::operator[](int i)
{
	int j = 0;
	while ()
	return vertexes[i];
}

std::list<LineSeg> Polygon::toEdges()
{
	std::list<LineSeg> edges;
	size_t j = 1;
	for (; j < vertexes.size(); j++)
		edges.push_back(LineSeg(vertexes[j - 1], vertexes[j]));
	edges.push_back(LineSeg(vertexes[j - 1], vertexes[0]));
	return edges;
}
