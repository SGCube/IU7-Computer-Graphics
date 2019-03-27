#include "draw.h"
#include "mainwindow.h"
#include <QGraphicsScene>
#include <QtMath>
#include <QPixmap>
#include <QDebug>

void draw_library(float sX, float sY, float eX, float eY, int col, int bgc_col, QGraphicsScene *scene)
{
    if (bgc_col == 1)
    {
        QPen pen(Qt::white);
        pen.setWidth(1);
        scene->addLine(sX, -sY, eX, -eY, pen);
    }
    else if (col == 0)
    {
        QPen pen(Qt::red);
        pen.setWidth(1);
        scene->addLine(sX, -sY, eX, -eY, pen);
    }

    else if (col == 1)
    {
        QPen pen(Qt::green);
        pen.setWidth(1);
        scene->addLine(sX, -sY, eX, -eY, pen);
    }
    else if (col == 2)
    {
        QPen pen(Qt::blue);
        pen.setWidth(1);
        scene->addLine(sX, -sY, eX, -eY, pen);
    }
    else if (col == 3)
    {
        QPen pen(Qt::black);
        pen.setWidth(1);
        scene->addLine(sX, -sY, eX, -eY, pen);
    }
}

void draw_cda(float sX, float sY, float eX, float eY, int col, int bgc_col, QGraphicsScene *scene, QPixmap px)
{
    QImage img = px.toImage();
    QRgb value;
    value = qRgb(255,0,0);

    for(int i=0; i < 100; i++)
    {
        for(int j=0; j < 200; j++)
            img.setPixel(i, j, value);
    }
    img.setPixel(1, 1, value);
    px = px.fromImage(img);
    double dx = eX - sX;
    double dy = eY - sY;
    double l;
    if (qFabs(dx) > qFabs(dy))
        l = qFabs(dx);
    else
        l = qFabs(dy);
    double sx = dx/l;
    double sy = dy/l;
    double x = sX;
    double y = sY;
    int i = 1;
    while (i <= l)
    {
        //scene->addLine(qFloor(x), -(qFloor(y-1)), qFloor(x), -(qFloor(y-1)), pen);
        //qDebug() << qFloor(x) << -(qFloor(y-1));
        x += sx;
        y += sy;
        i++;
    }

}

void draw_real(float sX, float sY, float eX, float eY, int col, int bgc_col, QGraphicsScene *scene)
{
    QPen pen(Qt::green);
    pen.setWidth(1);
    double x = sX;
    double y = sY;
    double dx = eX - sX;
    double dy = eY - sY;
    double sx, sy;
    if (dx > 0)
        sx = 1;
    else if (dx == 0)
        sx = 0;
    else
        sx = -1;
    if (dy > 0)
        sy = 1;
    else if (dy == 0)
        sy = 0;
    else
        sy = -1;
    dx = qFabs(dx);
    dy = qFabs(dy);
    int obmen;
    if (dx > dy)
        obmen = 0;
    else
        obmen = 1;
    double m = dy / dx;
    double e = m - 0.5;
    for (int i = 0; i <= dx; i++)
    {
        scene->addLine(x, -y, x, -y, pen);
        if (e >=0)
        {
            if (obmen == 0)
                y += sy;
            else
                x += sx;
            e -= 1;
        }
        if (e < 0)
        {
            if (obmen == 0)
                x += sx;
            else
                y += sy;
        }
        e += m;
    }
}

void draw_int(float sX, float sY, float eX, float eY, int col, int bgc_col, QGraphicsScene *scene)
{
    QPen pen(Qt::green);
    pen.setWidth(1);
    double x = sX;
    double y = sY;
    double dx = eX - sX;
    double dy = eY - sY;
    double sx, sy;
    if (dx > 0)
        sx = 1;
    else if (dx == 0)
        sx = 0;
    else
        sx = -1;
    if (dy > 0)
        sy = 1;
    else if (dy == 0)
        sy = 0;
    else
        sy = -1;
    dx = qFabs(dx);
    dy = qFabs(dy);
    int obmen;
    if (dx > dy)
        obmen = 0;
    else
        obmen = 1;
    int f1 = 2 * dy - dx;

    for (int i = 0; i <= dx; i++)
    {
        scene->addLine(x, -y, x, -y, pen);
        if (f1 >=0)
        {
            if (obmen == 0)
                y += sy;
            else
                x += sx;
            f1 -= 2 * dx;
        }
        if (f1 < 0)
        {
            if (obmen == 0)
                x += sx;
            else
                y += sy;
        }
        f1 += 2 * dy;
    }
}

void draw_step(float sX, float sY, float eX, float eY, int col, int bgc_col, QGraphicsScene *scene)
{
    QPen pen(Qt::green);
    pen.setWidth(1);
    int delta_x = abs(eX - sX);
    int delta_y = abs(eY - sY);
    int sign_x = (sX < eX ? 1 : -1);
    int sign_y = (sY < eY ? 1 : -1);

    double start_x = sX;
    double start_y = sY;

    double angle_tan = (delta_x != 0? (double)delta_y / (double)delta_x : 0);
    const int MAX_INTENSITY = 255;

    bool is_changed = false;

    if (delta_y > delta_x)
    {
        int temp = delta_y;
        delta_y = delta_x;
        delta_x = temp;

        is_changed = true;

        if (angle_tan != 0)
            angle_tan = 1 / angle_tan;
    }

    double correct_angle_tan = angle_tan * MAX_INTENSITY;
    double error = (double)MAX_INTENSITY / 2;
    double w = MAX_INTENSITY - correct_angle_tan;
    for(int i = 0; i <= delta_x; ++i)
    {
        scene->addLine(start_x, start_y, start_x, start_y, pen);

        if (error < w)
        {
            if (is_changed)
                start_y += sign_y;
            else
                start_x += sign_x;
            error += correct_angle_tan;
        }
        else
        {
            start_x += sign_x;
            start_y += sign_y;
            error -= w;
        }
    }
}

double round(double y)
{
    double yy = y - 1;
    return yy;
}
