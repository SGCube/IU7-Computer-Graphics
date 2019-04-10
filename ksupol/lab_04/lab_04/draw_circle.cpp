#include "draw_circle.h"
#include <QColor>
#include <QPen>
#include <QtMath>
#include <QGraphicsScene>
#include "math.h"
#include <QDebug>

#define PI 3.1415926535

void set_colour(int bgc_col, int col, QColor *c)
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

void draw_library(double x, double y, double rad, QColor *c, QGraphicsScene *scene)
{
    QPen pen;
    pen.setColor(*c);
    pen.setWidth(1);
    scene->addEllipse(x - rad, -y - rad, rad * 2, rad * 2, pen);
}

void draw_kanon(double x, double y, double r, QColor *c, QGraphicsScene *scene)
{
    QPen pen;
    pen.setColor(*c);
    pen.setWidth(1);

    double a = r / sqrt(2);
    double yy;
    double xx;

    for (xx = -a; xx <= a+1; xx++)
    {
        yy = sqrt(qPow(r, 2) - qPow(xx, 2));
        scene->addRect(xx + x, -(yy + y), 1, 1, pen);
        scene->addRect(xx + x, yy - y, 1, 1, pen);
    }
    for (yy = -a; yy <= a; yy++)
    {
        xx = sqrt(qPow(r, 2) - qPow(yy, 2));
        scene->addRect(xx + x, yy - y, 1, 1, pen);
        scene->addRect(x - xx, yy - y, 1, 1, pen);
    }
}

void draw_param(double x, double y, double r, QColor *c, QGraphicsScene *scene)
{
    QPen pen;
    pen.setColor(*c);
    pen.setWidth(1);

    double xx;
    double yy;
    //double t = 1 / r;
    for (int i = 0; i < 360; i++)
    {
        xx = x + r * cos(i);
        yy = r * sin(i) - y;
        scene->addRect(xx, yy, 1, 1, pen);
    }
}

void draw_bres(double xx, double yy, double r, QColor *c, QGraphicsScene *scene)
{
    QPen pen;
    pen.setColor(*c);
    pen.setWidth(1);

    int x = 0;
    int y = r;
    int gap = 0;
    int delta = 2 - 2 * r;
    while (y >= 0)
    {
        scene->addRect(x + xx, y - yy, 1, 1, pen);
        scene->addRect(-x + xx, y - yy, 1, 1, pen);
        scene->addRect(x + xx, -y - yy, 1, 1, pen);
        scene->addRect(-x + xx, -y - yy, 1, 1, pen);
        gap = 2 * (delta + y) - 1;
        if (delta < 0 && gap <= 0)
        {
            x++;
            delta += 2 * x + 1;
            continue;
        }
        if (delta > 0 && gap > 0)
        {
            y--;
            delta -= 2 * y + 1;
            continue;
        }
        x++;
        delta += 2 * (x - y);
        y--;
    }
}

void color_pix(int x0, int y0, int x, int y, QPen pen, QGraphicsScene *scene)
{
    scene->addRect(x + x0, y - y0, 1, 1, pen);
    scene->addRect(y + x0, x - y0, 1, 1, pen);
    scene->addRect(y + x0, -x - y0, 1, 1, pen);
    scene->addRect(x + x0, -y - y0, 1, 1, pen);
    scene->addRect(-x + x0, -y - y0, 1, 1, pen);
    scene->addRect(-y + x0, -x - y0, 1, 1, pen);
    scene->addRect(-y + x0, x - y0, 1, 1, pen);
    scene->addRect(-x + x0, y - y0, 1, 1, pen);
}

void draw_mid(double xx, double yy, double r, QColor *c, QGraphicsScene *scene)
{
    QPen pen;
    pen.setColor(*c);
    pen.setWidth(1);

    int x = 0;
    int y = r;
    int d = 1 - r;
    int p = 3;
    int q = -2 * r + 5;
    color_pix(xx, yy, x, y, pen, scene);
    while (y > x)
    {
        if (d<0)
        {
            d += p;
            p += 2;
            q += 2;
            x++;
        }
        else
        {
            d += q;
            p += 2;
            q += 4;
            x++;
            y--;
        }
        color_pix(xx, yy, x, y, pen, scene);
    }
}

void draw_cir_spectr(int s_r, int e_r, int k, QColor *c, QGraphicsScene *scene, int alg)
{
    double step = (e_r - s_r) / k;
    double r = s_r;


    for (int i = 0; i < k; i++)
    {
        if (alg == 0)
            draw_kanon(0, 0, r, c, scene);
        if (alg == 1)
            draw_param(0, 0, r, c, scene);
        if (alg == 2)
            draw_bres(0, 0, r, c, scene);
        if (alg == 3)
            draw_mid(0, 0, r, c, scene);
        if (alg == 4)
            draw_library(0, 0, r, c, scene);
        r += step;
    }
}
