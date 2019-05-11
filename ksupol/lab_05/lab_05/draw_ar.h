#ifndef DRAW_AR_H
#define DRAW_AR_H

#include "mainwindow.h"
#include "paint.h"

class Draw_ar : public QGraphicsScene
{
public:
    explicit Draw_ar(QImage *image, Paint *p,
                     MainWindow *w, QWidget *parent = nullptr);
private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    MainWindow *window;

    QImage *img;
    Paint *paint;
};

#endif // DRAW_AR_H
