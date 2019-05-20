#ifndef FILL_H
#define FILL_H

#include <QGraphicsScene>
#include <QColor>
#include <QDebug>
#include <QVector>
#include <QPoint>
#include <QPixmap>
#include <QImage>


void filling(QImage *img, QGraphicsScene *scene,
             QColor border_color, QColor fill_color, QColor bg_color, int x, int y, bool delay);

void find_new_pixel(QImage *img, QGraphicsScene *scene, QColor border_color,
                    QColor fill_color, QColor bg_color, int x, int y, int x_right, int x_left);

#endif // FILL_H
