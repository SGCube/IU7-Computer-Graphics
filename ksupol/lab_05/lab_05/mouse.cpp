#include "mouse.h"
#include <QDebug>

mouse::mouse(MainWindow *w) :
    QGraphicsScene(parent),
    window(w)
{
}

void mouse::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
        qDebug() << "right";
    /*
    int x = event->scenePos().x();
    int y = event->scenePos().y();
    int new_x = x, new_y = y;

    painter->begin(img);
    painter->set_edge();

    if (new_polygon->number_of_vertexes() == 0)
        painter->drawPoint(x, y);
    else
    {
        Point plast = new_polygon->last_point();
        if (parLine)
        {
            int xx = x - plast.x(), yy = plast.y() - y;
            if (yy > xx)
            {
                if (yy > -xx)
                    new_x = plast.x();
                else
                    new_y = plast.y();
            }
            else
            {
                if (yy > -xx)
                    new_y = plast.y();
                else
                    new_x = plast.x();
            }
        }
        painter->drawLine(plast.x(), plast.y(), new_x, new_y);
    }
    addPixmap(QPixmap::fromImage(*img));

    painter->end();

    new_polygon->add_point(Point(new_x, new_y));

    if (window)
    {
        window->add_point(Point(new_x, new_y));
        if (new_polygon->number_of_vertexes() > 2)
            window->lock_disable(false);
    }
    */
}
