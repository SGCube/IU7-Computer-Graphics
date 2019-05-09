#include "draw.h"
#include "mainwindow.h"
#include <math.h>
#include <QGraphicsScene>
#include <QtMath>
#include <QPixmap>
#include <QDebug>

#define R 150
#define MAX_INTENSITY 255

int sign(double x)
{
    if (x < 0)
        return -1;
    if (x > 0)
        return 1;
    return 0;
}

void set_colour(QColor *c, int bgc_col, int col)
{
    if (bgc_col == 1)
        c->setRgb(255, 255, 255);
    else if (col == 0)
        c->setRgb(0, 0, 0);
    else if (col == 1)
        c->setRgb(255, 0, 0);
    else if (col == 2)
        c->setRgb(255, 191, 0);
    else if (col == 3)
        c->setRgb(251, 255, 28);
    else if (col == 4)
        c->setRgb(34, 255, 0);
    else if (col == 5)
        c->setRgb(0, 255, 230);
    else if (col == 6)
        c->setRgb(34, 0, 255);
    else
        c->setRgb(221, 0, 255);
}

void draw_library(int sX, int sY, int eX, int eY, QColor *c, QGraphicsScene *scene)
{
    QPen pen;
    pen.setWidth(1);
    pen.setColor(*c);
    scene->addLine(sX, -sY, eX, -eY, pen);
}

void draw_dda(int sX, int sY, int eX, int eY, QColor *c, QGraphicsScene *scene)
{
    QPen pen;
    pen.setWidth(1);
    pen.setColor(*c);

    if (sX == eX && sY == eY)
    {
        scene->addRect(sX, -sY, 1, 1, pen);
        return;
    }
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
    for (int i = 1; i <= l + 1; i++)
    {
        scene->addRect(round(x), -round(y), 1, 1, pen);
        x += sx;
        y += sy;
    }
}

void draw_real(int sX, int sY, int eX, int eY, QColor *c, QGraphicsScene *scene)
{
    QPen pen;
    pen.setWidth(1);
    pen.setColor(*c);

    if (sX == eX && sY == eY)
    {
        scene->addRect(sX, -sY, 1, 1, pen);
        return;
    }
    int x = sX;
    int y = sY;
    float dx = eX - sX;
    float dy = eY - sY;
    int sign_x = sign(dx);
    int sign_y = sign(dy);
    dx = abs(dx);
    dy = abs(dy);

    int obmen = 0;
    if (dy >= dx)
    {
        obmen = 1;
        double t = dx;
        dx = dy;
        dy = t;
    }
    double m = dy / dx;
    double e = m - 0.5;
    for (int i = 1; i <= dx + 1; i++)
    {

        scene->addRect(x, -y, 1, 1, pen);
        if (e >= 0)
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

void draw_int(int sX, int sY, int eX, int eY, QColor *c, QGraphicsScene *scene)
{
    QPen pen;
    pen.setWidth(1);
    pen.setColor(*c);

    if (sX == eX && sY == eY)
    {
        scene->addRect(sX, -sY, 1, 1, pen);
        return;
    }
    int x = sX;
    int y = sY;
    int dx = eX - sX;
    int dy = eY - sY;
    int sx = sign(dx), sy = sign(dy);

    dx = abs(dx);
    dy = abs(dy);

    int obmen = 0;
    if (dy >= dx)
    {
        obmen = 1;
        int t = dx;
        dx = dy;
        dy = t;
    }
    int e = 2 * dy - dx;

    for (int i = 1; i <= dx + 1; i++)
    {
        scene->addRect(x, -y, 1, 1, pen);
        if (e >=0)
        {
            if (obmen == 0)
                y += sy;
            else
                x += sx;
            e -= 2 * dx;
        }
        if (e < 0)
        {
            if (obmen == 0)
                x += sx;
            else
                y += sy;
        }
        e += 2 * dy;
    }
}

void draw_step(int stX, int stY, int eX, int eY, QColor *c, QGraphicsScene *scene)
{
    QPen pen;
    pen.setWidth(1);
    pen.setColor(*c);

    if (stX == eX && stY == eY)
    {
        scene->addRect(stX, -stY, 1, 1, pen);
        return;
    }

    double dx = eX - stX;
    double dy = eY - stY;

    int sx = sign(dx);
    int sy = sign(dy);
    dx = abs(dx);
    dy = abs(dy);

    double x = stX;
    double y = stY;
    unsigned int obmen = 0;

    if (dy > dx)
    {
        double temp = dx;
        dx = dy;
        dy = temp;
        obmen = 1;
    }

    double tan;
    if (dx != 0)
        tan = dy / dx;
    else
        tan = 0;

    double m = tan * MAX_INTENSITY;
    double e = (double)MAX_INTENSITY / 2;
    double w = MAX_INTENSITY - m;
    for(int i = 1; i <= dx; i++)
    {
        c->setAlpha(MAX_INTENSITY - e);
        pen.setColor(*c);
        scene->addRect(x, -y, 1, 1, pen);
        if (e < w)
        {
            if (obmen == 0)
                x += sx;
            else
                y += sy;
            e += m;
        }
        else
        {
            x += sx;
            y += sy;
            e -= w;
        }
    }
}

void draw_spectrum(QColor *c, int alg, float degr, QGraphicsScene *scene)
{
    int kol = 360 / degr;
    double d = qDegreesToRadians(degr);

    float x = 1, y = 1;
    for (int i = 0; i < kol; i++)
    {
        x = R * qCos(d);
        y = R * qSin(d);
        if (alg == 0)
            draw_dda(0, 0, x, y, c, scene);
        else if (alg == 1)
            draw_real(0, 0, x, y, c, scene);
        else if (alg == 2)
            draw_int(0, 0, x, y, c, scene);
        else if (alg == 3)
            draw_step(0, 0, x, y, c, scene);
        else
            draw_library(0, 0, x, y, c, scene);
        d += qDegreesToRadians(degr);
    }
}
