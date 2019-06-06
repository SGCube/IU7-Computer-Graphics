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
    setSceneRect(0, 0, 800, 700);
    addPixmap(QPixmap::fromImage(*img));
}

void Draw_ar::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (window->line)
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
            if (x_left == -100 && y_bottom == -100)
            {
                x_left = event->scenePos().x();
                y_bottom = event->scenePos().y();
            }
            else
            {
                window->set_clipper = true;
                paint->begin(img);
                paint->set_pen();
                int x = event->scenePos().x();
                int y = event->scenePos().y();

                paint->put_line(x_left, y_bottom, x, y_bottom);
                paint->put_line(x_left, y_bottom, x_left, y);
                paint->put_line(x, y_bottom, x, y);
                paint->put_line(x_left, y, x, y);
                if (x < x_left)
                {
                    int x_tmp = x;
                    x = x_left;
                    x_left = x_tmp;
                }
                if (y_bottom > y)
                {
                    int y_tmp = y;
                    y = y_bottom;
                    y_bottom = y_tmp;
                }
                clipper->push_back(x_left);
                clipper->push_back(x);
                clipper->push_back(y_bottom);
                clipper->push_back(y);

                set_text(x_left, x, y_bottom, y);
                addPixmap(QPixmap::fromImage(*img));
                paint->end();
            }
        }
    }
}

void Draw_ar::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (window->line)
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
            if (x_left == -100 && y_bottom == -100)
                return;
            QImage img_2(*img);
            paint->begin(&img_2);
            paint->set_pen();
            int x = event->scenePos().x();
            int y = event->scenePos().y();

            paint->put_line(x_left, y_bottom, x, y_bottom);
            paint->put_line(x_left, y_bottom, x_left, y);
            paint->put_line(x, y_bottom, x, y);
            paint->put_line(x_left, y, x, y);

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

void Draw_ar::set_text(int x_left, int x_right, int y_bottom, int y_top)
{
    window->text->append("Координаты отсекателя:");
    window->text->append("X л = " + QString::number(x_left));
    window->text->append("X пр = " + QString::number(x_right));
    window->text->append("Y н = " + QString::number(y_bottom));
    window->text->append("Y в = " + QString::number(y_top));
}
