#include "edge.h"

Edge::Edge()
{
	end1 = Point(0, 0);
	end2 = Point(0, 1);
}

Edge::Edge(float x1, float y1, float x2, float y2)
{
	end1 = Point(x1, y1);
	end2 = Point(x2, y2);
}

Edge::Edge(Point p1, Point p2)
{
	end1 = p1;
	end2 = p2;
}

Point *Edge::p1()
{
	return &end1;
}

Point *Edge::p2()
{
	return &end2;
}

double Edge::length()
{
	return dist(end1, end2);
}

bool Edge::is_horizontal()
{
	return end2.y() == end1.y();
}

bool Edge::is_vertical()
{
	return end2.x() == end1.x();
}
