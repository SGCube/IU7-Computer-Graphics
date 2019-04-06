#include "draw.h"
#include "mainwindow.h"
#include <QGraphicsScene>
#include <QtMath>
#include <QPixmap>
#include <QDebug>

#define R 150

void draw_library(float sX, float sY, float eX, float eY, int col, int bgc_col, QGraphicsScene *scene)
{
    QPen pen;
    if (bgc_col == 1)
        pen.setColor("white");
    else if (col == 0)
        pen.setColor("red");
    else if (col == 1)
        pen.setColor("green");
    else if (col == 2)
        pen.setColor("blue");
    else
        pen.setColor("black");
    pen.setWidth(1);
    scene->addLine(sX, -sY, eX, -eY, pen);
}

void draw_dda(float sX, float sY, float eX, float eY, int col, int bgc_col, QGraphicsScene *scene)
{

    QPen pen;
    pen.setWidth(1);
    if (bgc_col == 1)
        pen.setColor("white");
    else if (col == 0)
        pen.setColor("red");
    else if (col == 1)
        pen.setColor("green");
    else if (col == 2)
        pen.setColor("blue");
    else
        pen.setColor("black");
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
        scene->addRect(my_round(x), -my_round(y), 1, 1, pen);
        x += sx;
        y += sy;
        i++;
    }
}

void draw_real(float sX, float sY, float eX, float eY, int col, int bgc_col, QGraphicsScene *scene)
{
    QPen pen;
    pen.setWidth(1);
    if (bgc_col == 1)
        pen.setColor("white");
    else if (col == 0)
        pen.setColor("red");
    else if (col == 1)
        pen.setColor("green");
    else if (col == 2)
        pen.setColor("blue");
    else
        pen.setColor("black");
    double x = sX;
    double y = sY;
    double dx = eX - sX;
    double dy = eY - sY;
    int sign_x = (dx > 0 ? 1 : -1);
    int sign_y = (dy > 0 ? 1 : -1);
    dx = qFabs(dx);
    dy = qFabs(dy);
    int obmen;
    if (dx > dy)
        obmen = 0;
    else
    {
        obmen = 1;
        double t = dx;
        dx = dy;
        dy = t;
    }
    double m = dy / dx;
    double e = m - 0.5;
    for (int i = 0; i <= dx; i++)
    {
        scene->addRect(x, -y, 1, 1, pen);
        if (e >=0)
        {
            if (obmen == 0)
                y += sign_y;
            else
                x += sign_x;
            e -= 1;
        }
        if (e < 0)
        {
            if (obmen == 0)
                x += sign_x;
            else
                y += sign_y;
        }
        e += m;
    }
}

void draw_int(float sX, float sY, float eX, float eY, int col, int bgc_col, QGraphicsScene *scene)
{
    QPen pen;
    pen.setWidth(1);
    if (bgc_col == 1)
        pen.setColor("white");
    else if (col == 0)
        pen.setColor("red");
    else if (col == 1)
        pen.setColor("green");
    else if (col == 2)
        pen.setColor("blue");
    else
        pen.setColor("black");
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
    {
        obmen = 1;
        double t = dx;
        dx = dy;
        dy = t;
    }
    int f1 = 2 * dy - dx;

    for (int i = 0; i <= dx; i++)
    {
        scene->addRect(x, -y, 1, 1, pen);
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
    QPen pen;
    QColor co;
    pen.setWidth(1);
    int dx = abs(eX - sX);
    int dy = abs(eY - sY);
    int sign_x = (sX < eX ? 1 : -1);
    int sign_y = (sY < eY ? 1 : -1);

    double x = sX;
    double y = sY;

    double angle_tan;
    if (dx != 0)
        angle_tan = dy / dx;
    else
        angle_tan = 0;
    const int MAX_INTENSITY = 255;

    int is_changed = 0;
    double error;

    if (angle_tan > 1)
    {
        double temp = dy;
        dy = dx;
        dx = temp;
        angle_tan = 1 / angle_tan;
        is_changed = 1;
    }
    if (angle_tan < 1)
        is_changed = 0;
    qDebug() << dx << dy;
    double correct_angle_tan = angle_tan * MAX_INTENSITY;
    error = MAX_INTENSITY / 2;
    double w = MAX_INTENSITY - correct_angle_tan;
    for(int i = 1; i <= dx; i++)
    {
        if (error < w)
        {
            if (is_changed == 0)
                y += sign_y;
            else
                x += sign_x;
            error += correct_angle_tan;
        }
        else
        {
            x += sign_x;
            y += sign_y;
            error -= w;
        }
        if (bgc_col == 1)
            co.setHsv(0, 0, 255, 255 - error);
        else if (col == 0)
            co.setHsv(0, 255, 255, 255 - error);
        else if (col == 1)
            co.setHsv(112, 199, 122, 255 - error);
        else if (col == 2)
            co.setHsv(227, 205, 205, 255 - error);
        else
            co.setHsv(0, 0, 0, 255 - error);
        pen.setColor(co);
        scene->addRect(x, -y, 1, 1, pen);
    }
}

void draw_spectrum(int col, int bgc_col, int alg, float degr, QGraphicsScene *scene)
{
    int kol = 360 / degr;
    double d = qDegreesToRadians(degr);

    double x = 1, y = 1;
    for (int i = 0; i < kol; i++)
    {
        x = R * qCos(d);
        y = R * qSin(d);
        if (alg == 0)
            draw_dda(0, 0, x, y, col, bgc_col, scene);
        else if (alg == 1)
            draw_real(0, 0, x, y, col, bgc_col, scene);
        else if (alg == 2)
            draw_int(0, 0, x, y, col, bgc_col, scene);
        else if (alg == 3)
            draw_step(0, 0, x, y, col, bgc_col, scene);
        else
            draw_library(0, 0, x, y, col, bgc_col, scene);
        d += qDegreesToRadians(degr);
    }
}

int my_round(double number)
{
    return (number >= 0) ? (int)(number + 0.5) : (int)(number - 0.5);
}
