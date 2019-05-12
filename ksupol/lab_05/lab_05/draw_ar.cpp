#include "draw_ar.h"
#include "check.h"

#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QDebug>

Draw_ar::Draw_ar(QImage *image, Paint *p, MainWindow *w, QWidget *parent):
    QGraphicsScene(parent),
    window(w),
    img(image),
    paint(p)
{
    setSceneRect(0, 0, 860, 660);
    addPixmap(QPixmap::fromImage(*img));
}

void Draw_ar::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "t";
    /*
    int x = event->scenePos().x();
    int y = event->scenePos().y();
    paint->begin(img);
    paint->color(0);
    paint->drawLine(0, 0, x, y);
    addPixmap(QPixmap::fromImage(*img));

    paint->end();
    */
}
