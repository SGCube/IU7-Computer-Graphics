#include "arc.h"

Arc::Arc(Point p = Point(0, 0), float a = 100, float b = 100, int ang = 180)
	: Ellipse::Ellipse(p, a, b)
{
	angle = ang;
	if (ang == 0)
		vertex_amount = 1;
	else if (ang >= 360)
		vertex_amount = 360;
	else
		vertex_amount /= 360 / ang;
}
