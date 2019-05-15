#ifndef FILL_H
#define FILL_H
#include <QImage>
#include <QColor>
#include <QVector>
#include <QPoint>
#include <QPixmap>
#include <QGraphicsScene>

void filling(QImage *img, QGraphicsScene *scene, QVector <QVector<QPoint>> *polygons_kit,
             QColor border_color, QColor fill_color, QColor bg_color);

#endif // FILL_H
