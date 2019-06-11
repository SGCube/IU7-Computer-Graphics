#include "paint.h"

Paint::Paint() : QPainter(), col(0, 0, 0)
{
    pen.setColor(col);
}

void Paint::colorClipper(int b)
{
    set_color(&clipper, b);
    pen.setColor(clipper);
}

void Paint::color(int b)
{
    set_color(&col, b);
    pen.setColor(col);
}

void Paint::set_pen()
{
    pen.setWidth(1);
    setPen(pen);
}

void Paint::set_double_pen()
{
    pen.setWidth(3);
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

void Paint::set_color(QColor *c, int col)
{
    switch (col)
    {
        case 0:
        {
            c->setRgb(0, 0, 0);
            break;
        }
        case 1:
        {
            c->setRgb(255, 0, 0);
            break;
        }
        case 2:
        {
            c->setRgb(255, 191, 0);
            break;
        }
        case 3:
        {
            c->setRgb(251, 255, 28);
            break;
        }
        case 4:
        {
            c->setRgb(34, 255, 0);
            break;
        }
        case 5:
        {
            c->setRgb(0, 255, 230);
            break;
        }
        case 6:
        {
            c->setRgb(34, 0, 255);
            break;
        }
        default:
            c->setRgb(221, 0, 255);
    }
}
