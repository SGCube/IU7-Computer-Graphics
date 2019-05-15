#include "fill.h"
#include <QTime>
#include <QApplication>
#include <QDebug>

void border_handling(QImage *img, QGraphicsScene *scene, QVector <QVector<QPoint>> *polygons_kit,
                     QColor border_color)
{
    for (int i = 0; i < polygons_kit->size(); i++)
    {
        QVector<QPoint> point = polygons_kit->value(i);
        for (int j = 1; j < point.size() - 1; j++)
        {
            if (point.value(j).y() < point.value(j-1).y() &&
                    point.value(j).y() < point.value(j+1).y())
                img->setPixelColor(point.value(j).x() + 1, point.value(j).y(), border_color);
            if (point.value(j).y() > point.value(j-1).y() &&
                    point.value(j).y() > point.value(j+1).y())
                img->setPixelColor(point.value(j).x() + 1, point.value(j).y(), border_color);
            if (point.value(j).y() == point.value(j-1).y())
            {
                int len = qAbs(point.value(j-1).x() - point.value(j).x());
                if (len % 2 != 0)
                    img->setPixelColor(point.value(j).x() + 1, point.value(j).y(), border_color);
            }
        }
    }
    scene->addPixmap(QPixmap::fromImage(*img));
}

void filling(QImage *img, QGraphicsScene *scene, QVector <QVector<QPoint>> *polygons_kit,
             QColor border_color, QColor fill_color, QColor bg_color, bool delay)
{
    QVector<QPoint> first = polygons_kit->value(0);
    int xmin = first.value(0).x();
    int xmax = first.value(0).x();
    int ymin = first.value(0).y();
    int ymax = first.value(0).y();
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
        if (delay)
        {
            scene->clear();
            scene->addPixmap(QPixmap::fromImage(*img));
            QTime dieTime = QTime::currentTime().addMSecs(delay);
            while(QTime::currentTime() < dieTime)
                QCoreApplication::processEvents(QEventLoop::AllEvents,
                                                delay);
        }

    }
    scene->addPixmap(QPixmap::fromImage(*img));
}
