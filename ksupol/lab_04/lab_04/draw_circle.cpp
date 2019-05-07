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

void draw_library(int x, int y, int rad, QColor *c, QGraphicsScene *scene)
{
    QPen pen;
    pen.setColor(*c);
    pen.setWidth(1);
    scene->addEllipse(x - rad, -y - rad, rad * 2, rad * 2, pen);
}

void draw_kanon(int x, int y, int r, QColor *c, QGraphicsScene *scene)
{
    QPen pen;
    pen.setColor(*c);
    pen.setWidth(1);

    float a = r / sqrt(2);
    float yy;
    float xx;

    for (xx = 0, yy = r; xx <= a + 1; xx++)
    {
        yy = sqrt(qPow(r, 2) - qPow(xx, 2));
        color_pix_cir(x, y, round(xx), round(yy), pen, scene);
    }
}

void draw_param(int x, int y, int r, QColor *c, QGraphicsScene *scene)
{
    QPen pen;
    pen.setColor(*c);
    pen.setWidth(1);

    float xx;
    float yy;
    float t = PI * r / 2;

    for (float tt = 0; tt <= t; tt++)
    {
        xx = x + r * cos(tt/r);
        yy = r * sin(tt/r) - y;
        color_pix_cir(x, y, round(xx), round(yy), pen, scene);
    }
}

void draw_bres(int xx, int yy, int r, QColor *c, QGraphicsScene *scene)
{
    QPen pen;
    pen.setColor(*c);
    pen.setWidth(1);

    int x = 0;
    int y = r;

    int d = 2 - 2 * r;
    int di, si;

    while (y >= 0)
    {
        scene->addRect(x + xx, y - yy, 1, 1, pen);
        scene->addRect(-x + xx, y - yy, 1, 1, pen);
        scene->addRect(x + xx, -y - yy, 1, 1, pen);
        scene->addRect(-x + xx, -y - yy, 1, 1, pen);
        if (d < 0)
        {
            di = 2 * (d + y) - 1;
            if (di <= 0)
            {
                x ++;
                d += 2 * x + 1;
            }
            else
            {
                x ++;
                y --;
                d += 2 * (x - y + 1);
            }
        }
        else if (d > 0)
        {
            si = 2 * (d - x) - 1;
            if (si <= 0)
            {
                x ++;
                y --;
                d += 2 * (x - y + 1);
            }
            else
            {
                y --;
                d += 1 - 2 * y;
            }
        }
        else
        {
            x ++;
            y --;
            d += 2 * (x - y + 1);
        }
    }
}

void color_pix_cir(int x0, int y0, int x, int y, QPen pen, QGraphicsScene *scene)
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

void draw_mid(int xx, int yy, int r, QColor *c, QGraphicsScene *scene)
{
    QPen pen;
    pen.setColor(*c);
    pen.setWidth(1);

    int x = 0;
    int y = r;
    int d = 1 - r;

    color_pix_cir(xx, yy, x, y, pen, scene);

    while (y > x)
    {
        if (d < 0)
        {
            x++;
            d += 2 * x + 1;
        }
        else
        {
            x++;
            y--;
            d += 2 * (x - y) + 1;
        }
        color_pix_cir(xx, yy, x, y, pen, scene);
    }
}

void draw_cir_spectr(int x, int y, int s_r, int e_r, int k, QColor *c, QGraphicsScene *scene, int alg)
{
    double step = (e_r - s_r) / k;
    int r = s_r;

    for (int i = 0; i < k; i++)
    {
        if (alg == 0)
            draw_kanon(x, y, r, c, scene);
        if (alg == 1)
            draw_param(x, y, r, c, scene);
        if (alg == 2)
            draw_bres(x, y, r, c, scene);
        if (alg == 3)
            draw_mid(x, y, r, c, scene);
        if (alg == 4)
            draw_library(x, y, r, c, scene);
        r += round(step);
    }
}
