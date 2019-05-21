#include "fill.h"
#include <QTime>
#include <QApplication>
#include <QDebug>
#include <math.h>

QPoint pointLeftTop(QVector <QVector<QPoint>> *polygons_kit)
{
	if (polygons_kit->size() == 0 && polygons_kit->value(0).size() == 0)
		return QPoint(0, 0);
	
	int xmin = polygons_kit->value(0).value(0).x();
	int ymin = polygons_kit->value(0).value(0).y();
	for (int i = 0; i < polygons_kit->size(); i++)
	{
		QVector<QPoint> points = polygons_kit->value(i);
		for (int j = 0; j < points.size(); j++)
		{
			for (int i = 1; i < points.size(); i++)
			{
				if (points.value(j).x() < xmin)
					xmin = points.value(j).x();
				if (points.value(j).y() < ymin)
					ymin = points.value(j).y();
			}
		}
	}
	return QPoint(xmin, ymin);
}

QPoint pointRightBottom(QVector <QVector<QPoint>> *polygons_kit)
{
	if (polygons_kit->size() == 0 && polygons_kit->value(0).size() == 0)
		return QPoint(0, 0);
	
	int xmax = polygons_kit->value(0).value(0).x();
	int ymax = polygons_kit->value(0).value(0).y();
	for (int i = 0; i < polygons_kit->size(); i++)
	{
		QVector<QPoint> points = polygons_kit->value(i);
		for (int j = 0; j < points.size(); j++)
		{
			for (int i = 1; i < points.size(); i++)
			{
				if (points.value(j).x() > xmax)
					xmax = points.value(j).x();
				if (points.value(j).y() > ymax)
					ymax = points.value(j).y();
			}
		}
	}
	return QPoint(xmax, ymax);
}


void border_handling(QImage *img, QGraphicsScene *scene, QVector <QVector<QPoint>> *polygons_kit,
                     QColor border_color)
{
	img->fill(Qt::white);
	for (int i = 0; i < polygons_kit->size(); i++)
	{
		QVector<QPoint> polygon = polygons_kit->value(i);
		for (int j = 1; j < polygon.size() + 1; j++)
		{
			QPoint pTop = polygon.value(j % polygon.size());
			QPoint pBottom = polygon.value(j - 1);
			if (pBottom.y() < pTop.y())
			{
				pTop = polygon.value(j - 1);
				pBottom = polygon.value(j % polygon.size());
			}
			
			double x = pTop.x();
			double dx = (double)(pTop.x() - pBottom.x())/(pTop.y() - pBottom.y());
			
			for (int y = pTop.y(); y < pBottom.y(); y++, x += dx)
			{
				int xx = round(x);
				if (img->pixelColor(xx, y) == border_color)
					img->setPixelColor(xx + 1, y, border_color);
				else
					img->setPixelColor(xx, y, border_color);
			}
		}
	}
    scene->addPixmap(QPixmap::fromImage(*img));
}

void filling(QImage *img, QGraphicsScene *scene, QVector <QVector<QPoint>> *polygons_kit,
             QColor border_color, QColor fill_color, QColor bg_color, bool delay)
{
	QPoint ltPoint = pointLeftTop(polygons_kit);
	QPoint rbPoint = pointRightBottom(polygons_kit);
	
	int ymax = rbPoint.y(), ymin = ltPoint.y();
	int xmax = rbPoint.x(), xmin = ltPoint.x();
	
    bool flag = false;
    for (int y = ymin; y <= ymax; y++)
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
