#include "fill.h"

void filling(QImage *img, QGraphicsScene *scene, QVector <QVector<QPoint>> *polygons_kit,
             QColor border_color, QColor fill_color, QColor bg_color)
{
    QVector<QPoint> first = polygons_kit->value(0);
    int xmin = first.value(0).x();
    int xmax = first.value(0).x();
    int ymin = first.value(0).y();
    int ymax = first.value(0).y();
    int xx;
    for (int i = 1; i < first.size(); i++)
    {
        if (first.value(i).x() < xmin)
            xmin = first.value(i).x();
        if (first.value(i).x() > xmax)
            xmax = first.value(i).x();
        if (first.value(i).y() < ymin)
            ymin = first.value(i).y();
        if (first.value(i).y() > ymax)
            ymax = first.value(i).y();
    }
    img->setPixelColor(xx + 1, ymin, border_color);
    bool flag = false;
    for (int y = ymax; y >= ymin; y--)
    {
        flag = false;
        for (int x = xmin; x <= xmax; x++)
        {
            if (img->pixelColor(x, y) == border_color)
            {
                if (flag == false)
                    flag = true;
                else
                    flag = false;
            }
            if (flag == true)
                img->setPixelColor(x, y, fill_color);
            else
                img->setPixelColor(x, y, bg_color);
        }
    }
    scene->addPixmap(QPixmap::fromImage(*img));
}
