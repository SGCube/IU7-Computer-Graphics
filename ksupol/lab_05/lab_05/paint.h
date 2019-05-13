﻿#ifndef PAINT_H
#define PAINT_H

#include <QPainter>

class Paint : public QPainter
{
public:
    Paint();
    void color(int b);
    void set_pen();
private:
    QPen pen;
    QColor col;
};

#endif // PAINT_H
