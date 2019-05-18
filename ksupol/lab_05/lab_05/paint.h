#ifndef PAINT_H
#define PAINT_H

#include <QGraphicsScene>
#include <QPainter>
#include "math.h"

class Paint : public QPainter
{
public:
    Paint();
    void color(int b);
    void set_pen();
    void put_line(int sX, int sY, int eX, int eY);
	void drawPolygons(QImage *img, QGraphicsScene *scene, QVector <QVector<QPoint>> *polygons_kit,
					  QColor border_color);
private:
    QPen pen;
    QColor col;
};

#endif // PAINT_H
