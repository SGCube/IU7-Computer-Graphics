#include "draw_ar.h"
#include "check.h"
#include "paint.h"
#include "mainwindow.h"

#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QDebug>

Draw_ar::Draw_ar(QImage *image, Paint *p, QVector<QVector<QPoint>> *polygons, QVector<QPoint> *pol,
                 MainWindow *w,
                 QWidget *parent):
    QGraphicsScene(parent),
    window(w),
    img(image),
    paint(p),
    polygons_kit(polygons),
    polygon(pol)
{
    setSceneRect(0, 0, 860, 660);
    addPixmap(QPixmap::fromImage(*img));
    bool hor_vert = false;
}

void Draw_ar::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        if (polygon->size() < 3)
            return;
        int x = polygon->value(0).x();
        int y = polygon->value(0).y();
        window->insert_into_table(QString::number(x), QString::number(y));
        //int b = window->col_b->currentIndex();
        paint->begin(img);
        //paint->color(b);
        paint->setPen(pen);
        int index = polygon->size() - 1;
        QPoint last = polygon->value(index);
        paint->drawLine(last.x(), last.y(), x, y);

        addPixmap(QPixmap::fromImage(*img));

        paint->end();

        window->insert_into_table("X", "Y");

        polygons_kit->push_back(*polygon);
        polygon->clear();
        return;
    }
    int x = event->scenePos().x();
    int y = event->scenePos().y();
    window->insert_into_table(QString::number(x), QString::number(y));

    paint->begin(img);
    //paint->color(b);
    if (polygon->size() > 0)
    {
        QPoint last = polygon->back();
        if (!hor_vert)
        {
            polygon->push_back(QPoint(x, y));
            paint->drawLine(last.x(), last.y(), x, y);
        }
        else
        {
            int a_x = qAbs(last.x() - x);
            int a_y = qAbs(last.y() - y);
            if (a_x >= a_y)
            {
                polygon->push_back(QPoint(x, last.y()));
                paint->drawLine(last.x(), last.y(), x, last.y());
            }
            else
            {
                polygon->push_back(QPoint(last.x(), y));
                paint->drawLine(last.x(), last.y(), last.x(), y);
            }
        }
    }
    else
    {
        polygon->push_back(QPoint(x, y));
        paint->drawPoint(x, y);
    }
    addPixmap(QPixmap::fromImage(*img));

    paint->end();

}

void Draw_ar::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (polygon->size() < 1)
        return;
    QImage img_2(*img);
    int x = event->scenePos().x();
    int y = event->scenePos().y();
    //qDebug() << x << y;
    paint->begin(&img_2);
    int index = polygon->size() - 1;
    QPoint last = polygon->value(index);
    qDebug() << last.x() << last.y();
    if (!hor_vert)
        paint->drawLine(last.x(), last.y(), x, y);
    else
    {
        int a_x = qAbs(last.x() - x);
        int a_y = qAbs(last.y() - y);
        if (a_x >= a_y)
            paint->drawLine(last.x(), last.y(), x, last.y());
        else
            paint->drawLine(last.x(), last.y(), last.x(), y);
    }
    addPixmap(QPixmap::fromImage(img_2));
    paint->end();
}

void Draw_ar::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Shift)
        hor_vert = true;
}

void Draw_ar::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Shift)
        hor_vert = false;
}
