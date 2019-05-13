#include "paint.h"
#include "check.h"

Paint::Paint() : QPainter(), col(0, 0, 0)
{
    pen.setColor(col);
}

void Paint::color(int b)
{
    set_color(&col, b);
    pen.setColor(col);
}

void Paint::set_pen()
{
    setPen(pen);
}
