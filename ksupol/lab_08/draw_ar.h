#ifndef DRAW_AR_H
#define DRAW_AR_H
#include "mainwindow.h"
#include "paint.h"
#include "math.h"

class Draw_ar : public QGraphicsScene
{

    int startX = 0, startY = 0;
    int amount = 0;
    bool hor_vert;
public:
    explicit Draw_ar(QImage *image, Paint *p, QVector<QLine> *segments, QVector<QPoint> *cutter,
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
    QVector<QLine> *lines;
    QVector<QPoint> *clipper;
};
#endif // DRAW_AR_H
