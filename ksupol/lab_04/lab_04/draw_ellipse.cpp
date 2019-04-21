#include "draw_ellipse.h"
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

    int a2 = a * a;
    int b2 = b * b;
    float x_end = a2 / sqrt(a2 + b2);
    float k = b / a;
    float x0, y0;
    float xx, yy;

    for (x0 = 0; x0 <= x_end; x0 += 1)
    {
        y0 = sqrt(a2 - x0 * x0) * k;
        xx = round(x0);
        yy = round(y0);

        scene->addRect(x + xx, -y - yy, 1, 1, pen);
        scene->addRect(x - xx, -y - yy, 1, 1, pen);
        scene->addRect(x + xx, -y + yy, 1, 1, pen);
        scene->addRect(x - xx, -y + yy, 1, 1, pen);
    }

    float y_end = b2 / sqrt(a2 + b2);
    k = 1 / k;

    for (y0 = 0; y0 <= y_end; y0 += 1)
    {
        x0 = sqrt(b2 - y0 * y0) * k;
        xx = round(x0);
        yy = round(y0);

        scene->addRect(x + xx, -y - yy, 1, 1, pen);
        scene->addRect(x - xx, -y - yy, 1, 1, pen);
        scene->addRect(x + xx, -y + yy, 1, 1, pen);
        scene->addRect(x - xx, -y + yy, 1, 1, pen);
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

void draw_el_mid(int x, int y, int a, int b, QColor *c, QGraphicsScene *scene)
{
    QPen pen;
    pen.setColor(*c);
    pen.setWidth(1);

    int a2 = a * a, b2 = b * b;
    int ad = 2 * a2, bd = 2 * b2;

    int mid = a2 / sqrt(a2 + b2);

    int x0 = 0, y0 = b;

    int d = -ad * b;
    double df = 0;
    double f = b2 - a2 * y + 0.25 * a2 + 0.5;

    for (x0 = 0; x0 <= mid; x0++)
    {
        scene->addRect(x + x0, -y - y0, 1, 1, pen);
        scene->addRect(x - x0, -y - y0, 1, 1, pen);
        scene->addRect(x + x0, -y + y0, 1, 1, pen);
        scene->addRect(x - x0, -y + y0, 1, 1, pen);

        if (f >= 0)
        {
            y0--;
            d += ad;
            f += d;
        }
        df += bd;
        f += df;
    }

    d = bd * x0;
    df = -ad * y0;
    f += -b2 * (x0 + 0.75) - a2 * (y0 - 0.75);

    for (; y0 >= 0; y0--)
    {
        scene->addRect(x + x0, -y - y0, 1, 1, pen);
        scene->addRect(x - x0, -y - y0, 1, 1, pen);
        scene->addRect(x + x0, -y + y0, 1, 1, pen);
        scene->addRect(x - x0, -y + y0, 1, 1, pen);

        if (f < 0)
        {
            x0++;
            d += bd;
            f += d;
        }
        df += ad;
        f += df;
    }

}

void draw_el_bres(int x, int y, int a, int b, QColor *c, QGraphicsScene *scene)
{
    QPen pen;
    pen.setColor(*c);
    pen.setWidth(1);

    int a2 = a * a;
    int b2 = b * b;

    int x0 = 0, y0 = b;
    int d = 4 * b2 + a2 * (1 - 4 * b);

    while (b2 * x0 <= a2 * y0)
    {
        scene->addRect(x + x0, -y - y0, 1, 1, pen);
        scene->addRect(x - x0, -y - y0, 1, 1, pen);
        scene->addRect(x + x0, -y + y0, 1, 1, pen);
        scene->addRect(x - x0, -y + y0, 1, 1, pen);

        if (d >= 0)
        {
            d -= 8 * a2 * (y0 - 1);
            y0--;
        }
        d += b2 * (8 * x0 + 12);
        x0++;
    }

    x0 = a, y0 = 0;
    d = 4 * a2 + b2 * (1 - 4 * a);
    while (a2 * y0 <= b2 * x0)
    {
        scene->addRect(x + x0, -y - y0, 1, 1, pen);
        scene->addRect(x - x0, -y - y0, 1, 1, pen);
        scene->addRect(x + x0, -y + y0, 1, 1, pen);
        scene->addRect(x - x0, -y + y0, 1, 1, pen);

        if (d >= 0)
        {
            d -= 8 * b2 * (x0 + 1);
            x0--;
        }
        d += a2 * (8 * y0 + 12);
        y0++;
    }
}

void draw_el_spectr(int s_a, int e_a, int s_b, int k, QColor *c, QGraphicsScene *scene, int alg)
{
    double step_a = (e_a - s_a) / k;
    double koef = e_a / s_a;
    double step_b = (koef * s_b - s_b) / k;

    int a = s_a;
    int b = s_b;

    for (int i = 0; i < k; i++)
    {
        if (alg == 0)
            draw_el_kanon(0, 0, a, b, c, scene);
        if (alg == 1)
            draw_el_param(0, 0, a, b, c, scene);
        if (alg == 2)
            draw_el_bres(0, 0, a, b, c, scene);
        if (alg == 3)
            draw_el_mid(0, 0, a, b, c, scene);
        if (alg == 4)
            draw_el_library(0, 0, a, b, c, scene);
        a += step_a;
        b += step_b;
    }
}
