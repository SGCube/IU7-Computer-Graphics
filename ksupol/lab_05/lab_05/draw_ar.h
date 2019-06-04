#ifndef DRAW_AR_H
#define DRAW_AR_H

#include "mainwindow.h"
#include "paint.h"
#include "math.h"

class Draw_ar : public QGraphicsScene
{
public:
    explicit Draw_ar(QImage *image, Paint *p, QVector<QVector<QPoint> > *polygons, QVector<QPoint> *pol,
                     MainWindow *w, QWidget *parent = nullptr);


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    MainWindow *window;

    QImage *img;
    Paint *paint;
    QVector<QVector<QPoint>> *polygons_kit;
    QVector<QPoint> *polygon;
    bool hor_vert;
};

#endif // DRAW_AR_H
