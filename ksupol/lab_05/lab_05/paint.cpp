#include "paint.h"
#include <QString>
#include <QGraphicsScene>
#include <QDebug>

void paint(int amount, struct point *points, QGraphicsScene *scene, QColor *c)
{
    QPen pen;
    pen.setWidth(2);
    pen.setColor(*c);
    for (int i = 1; i < amount; i++)
    {
        scene->addLine(points[i - 1].x, -points[i - 1].y, points[i].x, -points[i].y, pen);
    }
}

void set_color(QColor *c, int col)
{
    if (col == 0)
        c->setRgb(0, 0, 0);
    else if (col == 1)
        c->setRgb(255, 0, 0);
    else if (col == 2)
        c->setRgb(255, 191, 0);
    else if (col == 3)
        c->setRgb(251, 255, 28);
    else if (col == 4)
        c->setRgb(34, 255, 0);
    else if (col == 5)
        c->setRgb(0, 255, 230);
    else if (col == 6)
        c->setRgb(34, 0, 255);
    else
        c->setRgb(221, 0, 255);
}
