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

Point Polygon::operator[](int i)
{
	return vertexes[i];
}

vector<Edge> Polygon::set_to_edges(vector<Polygon> set)
{
	vector<Edge> edges;
	for (size_t i = 0; i < set.size(); i++)
	{
		int j = 1;
		for (; j < set[i].number_of_vertexes(); j++)
			edges.push_back(Edge(set[i][j - 1], set[i][j]));
		edges.push_back(Edge(set[i][j - 1], set[i][0]));
	}
	return edges;
}
