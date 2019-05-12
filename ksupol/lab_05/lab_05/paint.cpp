#include "paint.h"
#include "check.h"

Paint::Paint() : QPainter()
{

}

void Paint::color(int b)
{
    set_color(col, b);
    pen.setColor(*col);
    setPen(pen);
}
