#include "draw_ar.h"
#include "paint.h"
#include "mainwindow.h"

#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QDebug>

Draw_ar::Draw_ar(QImage *image, Paint *p, QVector<QLine> *segments, QVector<int> *cutter,
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
            window->insert_into_table(QString::number(startX), QString::number(startY));
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
                window->insert_into_table(QString::number(x), QString::number(y));
            }
            else
            {
                int a_x = qAbs(startX - x);
                int a_y = qAbs(startY - y);
                if (a_x >= a_y)
                {
                    lines->push_back(QLine(startX, startY, x, startY));
                    paint->put_line(startX, startY, x, startY);
                    window->insert_into_table(QString::number(x), QString::number(startY));
                }
                else
                {
                    lines->push_back(QLine(startX, startY, startX, y));
                    paint->put_line(startX, startY, startX, y);
                    window->insert_into_table(QString::number(startX), QString::number(y));
                }
            }
            addPixmap(QPixmap::fromImage(*img));
            paint->end();
            amount = 0;
            window->insert_into_table("X", "Y");
        }
    }
    else
    {
        if (window->set_clipper == false)
        {
            window->text->append("Координаты отсекателя:");
            paint->begin(img);
            paint->set_pen();
            int x = event->scenePos().x();
            int y = event->scenePos().y();
            int h = window->h;
            int w = window->w;
            if (h % 2 != 0 && w % 2 != 0)
            {
                set_text(x - w/2 + 1, x + w/2, y + h/2 + 1, y - h/2);
                paint->put_line(x - w/2 + 1, y - h/2, x + w/2, y - h/2);
                paint->put_line(x - w/2 + 1, y + h/2, x + w/2, y + h/2);
                paint->put_line(x - w/2, y + h/2 + 1, x - w/2, y - h/2);
                paint->put_line(x + w/2, y + h/2 + 1, x + w/2, y - h/2);
                clipper->push_back(x - w/2 + 1);
                clipper->push_back(x + w/2);
                clipper->push_back(y - h/2);
                clipper->push_back(y + h/2 + 1);
            }
            else if (h % 2 != 0 && w % 2 == 0)
            {
                set_text(x + w/2, x - w/2, y + h/2 + 1, y - h/2);
                paint->put_line(x - w/2, y - h/2, x + w/2, y - h/2);
                paint->put_line(x - w/2, y + h/2, x + w/2, y + h/2);
                paint->put_line(x - w/2, y + h/2 + 1, x - w/2, y - h/2);
                paint->put_line(x + w/2, y + h/2 + 1, x + w/2, y - h/2);
                clipper->push_back(x - w/2);
                clipper->push_back(x + w/2);
                clipper->push_back(y - h/2);
                clipper->push_back(y + h/2 + 1);
            }
            else if (h % 2 == 0 && w % 2 != 0)
            {
                set_text(x + w/2, x - w/2 + 1, y + h/2, y - h/2);
                paint->put_line(x - w/2 + 1, y - h/2, x + w/2, y - h/2);
                paint->put_line(x - w/2 + 1, y + h/2, x + w/2, y + h/2);
                paint->put_line(x - w/2, y + h/2, x - w/2, y - h/2);
                paint->put_line(x + w/2, y + h/2, x + w/2, y - h/2);
                clipper->push_back(x - w/2 + 1);
                clipper->push_back(x + w/2);
                clipper->push_back(y - h/2);
                clipper->push_back(y + h/2);
            }
            else
            {
                set_text(x + w/2, x - w/2, y + h/2, y - h/2);
                paint->put_line(x - w/2, y - h/2, x + w/2, y - h/2);
                paint->put_line(x - w/2, y + h/2, x + w/2, y + h/2);
                paint->put_line(x - w/2, y + h/2, x - w/2, y - h/2);
                paint->put_line(x + w/2, y + h/2, x + w/2, y - h/2);
                clipper->push_back(x - w/2);
                clipper->push_back(x + w/2);
                clipper->push_back(y - h/2);
                clipper->push_back(y + h/2);
            }
            addPixmap(QPixmap::fromImage(*img));
            paint->end();
            window->set_clipper = true;
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
            QImage img_2(*img);
            paint->begin(&img_2);
            paint->set_pen();
            int x = event->scenePos().x();
            int y = event->scenePos().y();
            int h = window->h;
            int w = window->w;
            if (h % 2 != 0 && w % 2 != 0)
            {
                paint->put_line(x - w/2 + 1, y - h/2, x + w/2, y - h/2);
                paint->put_line(x - w/2 + 1, y + h/2, x + w/2, y + h/2);
                paint->put_line(x - w/2, y + h/2 + 1, x - w/2, y - h/2);
                paint->put_line(x + w/2, y + h/2 + 1, x + w/2, y - h/2);
            }
            else if (h % 2 != 0 && w % 2 == 0)
            {
                paint->put_line(x - w/2, y - h/2, x + w/2, y - h/2);
                paint->put_line(x - w/2, y + h/2, x + w/2, y + h/2);
                paint->put_line(x - w/2, y + h/2 + 1, x - w/2, y - h/2);
                paint->put_line(x + w/2, y + h/2 + 1, x + w/2, y - h/2);
            }
            else if (h % 2 == 0 && w % 2 != 0)
            {
                paint->put_line(x - w/2 + 1, y - h/2, x + w/2, y - h/2);
                paint->put_line(x - w/2 + 1, y + h/2, x + w/2, y + h/2);
                paint->put_line(x - w/2, y + h/2, x - w/2, y - h/2);
                paint->put_line(x + w/2, y + h/2, x + w/2, y - h/2);
            }
            else
            {
                paint->put_line(x - w/2, y - h/2, x + w/2, y - h/2);
                paint->put_line(x - w/2, y + h/2, x + w/2, y + h/2);
                paint->put_line(x - w/2, y + h/2, x - w/2, y - h/2);
                paint->put_line(x + w/2, y + h/2, x + w/2, y - h/2);
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

void Draw_ar::set_text(int x_right, int x_left, int y_top, int y_bottom)
{
    window->text->append("X л = " + QString::number(x_left));
    window->text->append("X пр = " + QString::number(x_right));
    window->text->append("Y в = " + QString::number(y_top));
    window->text->append("Y н = " + QString::number(y_bottom));
}
