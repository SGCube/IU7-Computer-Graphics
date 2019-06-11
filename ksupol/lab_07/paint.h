#ifndef PAINT_H
#define PAINT_H

#include <QPainter>
#include "math.h"

class Paint : public QPainter
{
public:
    Paint();
    void color(int b);
    void set_pen();
    void put_line(int sX, int sY, int eX, int eY);
    void set_color(QColor *c, int col);
    void colorClipper(int b);
    void set_double_pen();
private:
    QPen pen;
    QColor col;
    QColor clipper;
};

#endif // PAINT_H
