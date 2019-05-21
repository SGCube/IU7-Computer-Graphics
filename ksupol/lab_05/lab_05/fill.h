#ifndef FILL_H
#define FILL_H
#include <QImage>
#include <QColor>
#include <QVector>
#include <QPoint>
#include <QPixmap>
#include <QGraphicsScene>

void border_handling(QImage *img, QGraphicsScene *scene, QVector <QVector<QPoint>> *polygons_kit,
                     QColor border_color);

void filling(QImage *img, QGraphicsScene *scene, QVector <QVector<QPoint>> *polygons_kit,
             QColor border_color, QColor fill_color, QColor bg_color, bool delay);
#endif // FILL_H
