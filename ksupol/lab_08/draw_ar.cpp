#include "draw_ar.h"
#include "paint.h"
#include "mainwindow.h"

#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QDebug>

Draw_ar::Draw_ar(QImage *image, Paint *p, QVector<QLine> *segments, QVector<QPoint> *cutter,
                 MainWindow *w,
                 QWidget *parent):
    QGraphicsScene(parent),
    window(w),
    img(image),
    paint(p),
    lines(segments),
    clipper(cutter)
{
    setSceneRect(0, 0, 860, 660);
    addPixmap(QPixmap::fromImage(*img));
}

void Draw_ar::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (window->line_or_clipper)
    {
        if (amount == 0)
        {
            startX = event->scenePos().x();
            startY = event->scenePos().y();
            window->insert_into_table_lines(QString::number(startX), QString::number(startY));
            amount++;
        }
        else
        {
            int x = event->scenePos().x();
            int y = event->scenePos().y();
            paint->begin(img);
            paint->set_pen();
            if (!hor_vert)
            {
                lines->push_back(QLine(startX, startY, x, y));
                paint->put_line(startX, startY, x, y);
                window->insert_into_table_lines(QString::number(x), QString::number(y));
            }
            else
            {
                int a_x = qAbs(startX - x);
                int a_y = qAbs(startY - y);
                if (a_x >= a_y)
                {
                    lines->push_back(QLine(startX, startY, x, startY));
                    paint->put_line(startX, startY, x, startY);
                    window->insert_into_table_lines(QString::number(x), QString::number(startY));
                }
                else
                {
                    lines->push_back(QLine(startX, startY, startX, y));
                    paint->put_line(startX, startY, startX, y);
                    window->insert_into_table_lines(QString::number(startX), QString::number(y));
                }
            }
            addPixmap(QPixmap::fromImage(*img));
            paint->end();
            amount = 0;
            window->insert_into_table_lines("X", "Y");
        }
    }
    else
    {
        if (window->set_clipper == false)
        {
            if (event->button() == Qt::RightButton)
            {
                if (clipper->size() < 3)
                    return;
                int x = clipper->value(0).x();
                int y = clipper->value(0).y();
                window->insert_into_table_clipper(QString::number(x), QString::number(y));
                paint->begin(img);
                paint->set_pen();
                QPoint last = clipper->back();
                paint->put_line(last.x(), last.y(), x, y);
                addPixmap(QPixmap::fromImage(*img));
                paint->end();
                window->insert_into_table_clipper("X", "Y");
                clipper->clear();
                return;
            }
            int x = event->scenePos().x();
            int y = event->scenePos().y();
            window->insert_into_table_clipper(QString::number(x), QString::number(y));

            paint->begin(img);
            paint->set_pen();
            if (clipper->size() > 0)
            {
                QPoint last = clipper->back();
                if (!hor_vert)
                {
                    clipper->push_back(QPoint(x, y));
                    paint->put_line(last.x(), last.y(), x, y);
                }
                else
                {
                    int a_x = qAbs(last.x() - x);
                    int a_y = qAbs(last.y() - y);
                    if (a_x >= a_y)
                    {
                        clipper->push_back(QPoint(x, last.y()));
                        paint->put_line(last.x(), last.y(), x, last.y());
                    }
                    else
                    {
                        clipper->push_back(QPoint(last.x(), y));
                        paint->put_line(last.x(), last.y(), last.x(), y);
                    }
                }
            }
            else
            {
                clipper->push_back(QPoint(x, y));
                paint->drawPoint(x, y);
            }
            addPixmap(QPixmap::fromImage(*img));

            paint->end();
        }
    }
}

void Draw_ar::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (window->line_or_clipper)
    {
        if (amount == 0)
            return;
        QImage img_2(*img);
        paint->begin(&img_2);
        paint->set_pen();
        int x = event->scenePos().x();
        int y = event->scenePos().y();
        if (!hor_vert)
            paint->put_line(startX, startY, x, y);
        else
        {
            int a_x = qAbs(startX - x);
            int a_y = qAbs(startY - y);
            if (a_x >= a_y)
                paint->put_line(startX, startY, x, startY);
            else
                paint->put_line(startX, startY, startX, y);
        }
        addPixmap(QPixmap::fromImage(img_2));
        paint->end();
    }
    else
    {
        if (window->set_clipper == false)
        {
            if (clipper->size() == 0)
                return;
            QImage img_2(*img);
            paint->begin(&img_2);
            paint->set_pen();
            int x = event->scenePos().x();
            int y = event->scenePos().y();
            QPoint last = clipper->back();

            if (!hor_vert)
                paint->put_line(last.x(), last.y(), x, y);
            else
            {
                int a_x = qAbs(last.x() - x);
                int a_y = qAbs(last.y() - y);
                if (a_x >= a_y)
                    paint->put_line(last.x(), last.y(), x, last.y());
                else
                    paint->put_line(last.x(), last.y(), last.x(), y);
            }
            addPixmap(QPixmap::fromImage(img_2));
            paint->end();
        }
    }
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
