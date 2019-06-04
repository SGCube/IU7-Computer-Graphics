#include "paint.h"
#include "check.h"
#include <QDebug>
#include <QGraphicsScene>

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

void Paint::put_line(int sX, int sY, int eX, int eY)
{
    float dx = eX - sX;
    float dy = eY - sY;
    float l;
    if (qAbs(dx) > qAbs(dy))
        l = qAbs(dx);
    else
        l = qAbs(dy);
    float sx = dx/l;
    float sy = dy/l;
    float x = sX;
    float y = sY;
    for (int i = 1; i <= l + sx + 1; i++)
    {
        drawPoint(QPoint(round(x), round(y)));
        x += sx;
        y += sy;
    }
}
