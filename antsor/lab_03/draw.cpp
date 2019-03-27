#include <math.h>

#include "draw.h"

void draw_line_dda(QImage *img, Point p1, Point p2, QColor color)
{
	if (p1 == p2)
	{
		img->setPixel(p1.x(), p1.y(), color.rgb());
		return;
	}
	double xlen = p2.x() - p1.x(), ylen = p2.y() - p1.y();
	double len;
	if (fabs(xlen) > fabs(ylen))
		len =fabs(xlen);
	else
		len = fabs(ylen);
	double dx = xlen / len, dy = ylen / len;
	double x = p1.x(), y = p1.y();
	int i = 1;
	while (i <= dx + len)
	{
		img->setPixel(round(x), round(y), color.rgb());
		x += dx;
		y += dy;
		i++;
	}
}
