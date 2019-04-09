#include <math.h>

#include "circle.h"

void draw_circle_lib(QPainter *painter, Point pc, double r)
{
	painter->drawEllipse(QPointF(pc.x(), pc.y()), r, r);
}
