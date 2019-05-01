#include "polygon.h"
using std::vector;

Polygon::Polygon()
{
	
}

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
