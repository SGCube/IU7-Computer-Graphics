#include "draw_ellipse.h"
#include "draw_circle.h"
#include <QColor>
#include <QPen>
#include <QtMath>
#include <QGraphicsScene>
#include "math.h"

#define PI 3.1415926535


void draw_el_library(int x, int y, int a, int b, QColor *c, QGraphicsScene *scene)
{
    QPen pen;
    pen.setColor(*c);
    pen.setWidth(1);

    scene->addEllipse(x - a, -y - b, a * 2, b * 2, pen);
}


void draw_el_kanon(int x, int y, float a, float b, QColor *c, QGraphicsScene *scene)
{
    QPen pen;
    pen.setColor(*c);
    pen.setWidth(1);

    float n = qPow(a, 2) / sqrt(qPow(a, 2) + qPow(b, 2));
    float k = b / a;
    float xx, yy;

    for (xx = 0; xx <= n; xx++)
    {
        yy = sqrt(qPow(a, 2) - qPow(xx, 2)) * k;
        scene->addRect(x + round(xx), -y - round(yy), 1, 1, pen);
        scene->addRect(x - round(xx), -y - round(yy), 1, 1, pen);
        scene->addRect(x + round(xx), -y + round(yy), 1, 1, pen);
        scene->addRect(x - round(xx), -y + round(yy), 1, 1, pen);
    }

    n = qPow(b, 2) / sqrt(qPow(a, 2) + qPow(b, 2));
    k = 1 / k;

    for (yy = 0; yy <= n; yy++)
    {
        xx = sqrt(qPow(b, 2) - qPow(yy, 2)) * k;
        scene->addRect(x + round(xx), -y - round(yy), 1, 1, pen);
        scene->addRect(x - round(xx), -y - round(yy), 1, 1, pen);
        scene->addRect(x + round(xx), -y + round(yy), 1, 1, pen);
        scene->addRect(x - round(xx), -y + round(yy), 1, 1, pen);
    }
}

void draw_el_param(int x, int y, float a, float b, QColor *c, QGraphicsScene *scene)
{
    QPen pen;
    pen.setColor(*c);
    pen.setWidth(1);

    float xx;
    float yy;
    float t = 1 / a;

    for (float tt = 0; tt < 2 * PI; tt += t)
    {
        xx = a * cos(tt);
        yy = b * sin(tt);
        scene->addRect(round(xx) + x, -round(yy) - y, 1, 1, pen);
    }
}

void color_pixel(int x0, int y0, int x, int y, QPen pen, QGraphicsScene *scene)
{
    scene->addRect(x + x0, y - y0, 1, 1, pen);
    scene->addRect(x + x0, -y - y0, 1, 1, pen);
    scene->addRect(-x + x0, -y - y0, 1, 1, pen);
    scene->addRect(-x + x0, y - y0, 1, 1, pen);
}

void draw_el_bres(int xx, int yy, int a, int b, QColor *c, QGraphicsScene *scene)
{
    QPen pen;
    pen.setColor(*c);
    pen.setWidth(1);

    int a2 = a * a;
    int b2 = b * b;

    int x = 0;
    int y = b;

    int d = b2 - a2 * (2 * b + 1);
    int di, si;

    while (y >= 0)
    {
        color_pixel(xx, yy, x, y, pen, scene);
        if (d < 0)
        {
            di = 2 * d - 2 * a2 * y + a2;
            if (di < 0)
            {
                x += 1;
                d += b2 * (2 * x + 3);
            }
            else
            {
                x += 1;
                y -= 1;
                d += b2 * (2 * x + 3) + a2 * (-2 * y + 3);
            }
        }
        else if (d > 0)
        {
            si = 2 * d - 2 * b2 * x - b2;
            if (si < 0)
            {
                x += 1;
                y -= 1;
                d += b2 * (2 * x + 3) + a2 * (-2 * y + 3);
            }
            else
            {
                y -= 1;
                d += a2 * (-2 * y + 3);
            }
        }
    }
}

void draw_el_mid(int xx, int yy, int a, int b, QColor *c, QGraphicsScene *scene)
{
    QPen pen;
    pen.setColor(*c);
    pen.setWidth(1);

    int a2 = a * a;
    int b2 = b * b;

    int x = 0;
    int y = b;

    float p = b2 - a2 * b + 0.25 * a2;
    while (2 * b2 * x < 2 * a2 * y)
    {
        color_pixel(xx, yy, x, y, pen, scene);
        if (p < 0)
        {
            x++;
            p += 2 * b2 * x + b2;
        }
        else
        {
            x++;
            y--;
            p += 2 * b2 * x - 2 * a2 * y + b2;
        }
    }

    p = b2 * qPow(x + 0.5, 2) + a2 * qPow(y - 1, 2) - a2 * b2;
    while (y != 0)
    {
        color_pixel(xx, yy, x, y, pen, scene);
        if (p > 0)
        {
            y--;
            p += a2 - (2 * a2 * y);
        }
        else
        {
            x++;
            y--;
            p += 2 * b2 * x - 2 * a2 * y + a2;
        }
    }
}

void draw_el_spectr(int x, int y, int s_a, int e_a, int s_b, int k, QColor *c, QGraphicsScene *scene, int alg)
{
    double step_a = (e_a - s_a) / k;
    double koef = e_a / s_a;
    double step_b = (koef * s_b - s_b) / k;

    int a = s_a;
    int b = s_b;

    for (int i = 0; i < k; i++)
    {
        if (alg == 0)
            draw_el_kanon(x, y, a, b, c, scene);
        if (alg == 1)
            draw_el_param(x, y, a, b, c, scene);
        if (alg == 2)
            draw_el_bres(x, y, a, b, c, scene);
        if (alg == 3)
            draw_el_mid(x, y, a, b, c, scene);
        if (alg == 4)
            draw_el_library(x, y, a, b, c, scene);
        a += step_a;
        b += step_b;
    }
}
