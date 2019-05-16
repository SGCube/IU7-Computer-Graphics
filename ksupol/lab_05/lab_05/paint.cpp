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

void Paint::drawPolygons(QImage *img, QGraphicsScene *scene, QVector <QVector<QPoint>> *polygons_kit,
						 QColor border_color)
{
	pen.setColor(border_color);
	setPen(pen);
	begin(img);
	for (int i = 0; i < polygons_kit->size(); i++)
	{
		QVector<QPoint> polygon = polygons_kit->value(i);
		for (int j = 1; j < polygon.size(); j++)
		{
			QPoint p1 = polygon.value(j - 1);
			QPoint p2 = polygon.value(j);
			put_line(p1.x(), p1.y(), p2.x(), p2.y());
		}	
		QPoint p1 = polygon.value(polygon.size() - 1);
		QPoint p2 = polygon.value(0);
		put_line(p1.x(), p1.y(), p2.x(), p2.y());		
	}
	scene->addPixmap(QPixmap::fromImage(*img));
	end();
}
