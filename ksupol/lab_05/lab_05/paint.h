#ifndef ARRAY_H
#define ARRAY_H
#include <QGraphicsScene>

struct point
{
    int x;
    int y;
};
void paint(int amount, struct point *points, QGraphicsScene *scene, QColor *c);

void set_color(QColor *color, int b);

#endif // ARRAY_H
