#ifndef MOUSE_H
#define MOUSE_H

#include <QGraphicsSceneMouseEvent>

class mouse : public QGraphicsScene
{
public:
    explicit mouse(MainWindow *w);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

};


#endif // MOUSE_H
