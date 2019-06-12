#include <cmath>

#include "clipper.h"
#include "vector.hpp"

void Clipper::clip(std::vector<Polygon> &polygons, Painter &painter)
{
	for (size_t i = 0; i < polygons.size(); i++)
		clipPolygon(polygons[i], painter);
}

void Clipper::clipPolygon(Polygon &polygon, Painter &painter)
{
	
}
