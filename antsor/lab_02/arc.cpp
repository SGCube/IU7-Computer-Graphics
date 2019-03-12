#include "arc.h"

Arc::Arc(Point p, float a, float b, int ang) : Ellipse::Ellipse(p, a, b)
{
	angle = ang;
	if (ang == 0)
		set_vamount(1);
	else if (ang < 360)
		set_vamount(vamount() / 360 * ang);
}
