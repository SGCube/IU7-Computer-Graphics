#include "draw_ellipse.h"
#include <QColor>
#include <QPen>
#include <QtMath>
#include <QGraphicsScene>
#include "math.h"


void draw_el_library(double x, double y, double a, double b, QColor *c, QGraphicsScene *scene)
{
    QPen pen;
    pen.setColor(*c);
    pen.setWidth(1);

    scene->addEllipse(x - a, -y - b, a * 2, b * 2, pen);
}


void draw_el_kanon(double x, double y, double a, double b, QColor *c, QGraphicsScene *scene)
{
    QPen pen;
    pen.setColor(*c);
    pen.setWidth(1);

    double yy;
    double xx;

    for (xx = -a; xx <= a+1; xx++)
    {
        yy = sqrt(1 - qPow(xx, 2));
        scene->addRect(xx + x, -(yy + y), 1, 1, pen);
        scene->addRect(xx + x, yy - y, 1, 1, pen);
    }
    for (yy = -a; yy <= a; yy++)
    {
        xx = sqrt(1 - qPow(yy, 2));
        scene->addRect(xx + x, yy - y, 1, 1, pen);
        scene->addRect(x - xx, yy - y, 1, 1, pen);
    }
}

void draw_el_param(double x, double y, double a, double b, QColor *c, QGraphicsScene *scene)
{
    QPen pen;
    pen.setColor(*c);
    pen.setWidth(1);

    double xx;
    double yy;
    //double t = 1 / r;
    for (int i = 0; i < 360; i++)
    {
        xx = a * cos(i);
        yy = b * sin(i);
        scene->addRect(xx + x, -yy - y, 1, 1, pen);
    }
}

void draw_el_mid(double x, double y, double a, double b, QColor *c, QGraphicsScene *scene)
{
    double x0 = 0;
    double y0 = b;

    double pl0 = qPow(b, 2) - qPow(a, 2)*b + 1/4*qPow()a, 2;
    /*
    while (2 * qPow(b, 2) * x >= 2 * qPow(a, 2) * y)
    {

    }
    */
}

void draw_el_bres(double x, double y, double a, double b, QColor *c, QGraphicsScene *scene)
{

}
