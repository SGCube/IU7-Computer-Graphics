#include "fill.h"
#include <QTime>
#include <QApplication>

void find_new_pixel(QImage *img, QGraphicsScene *scene, QColor border_color,
                    QColor fill_color, QColor bg_color, QVector <QPoint> *stack, int y, int x_right, int x_left)
{
    bool f;
    int x = x_left;
    int xn;
    while (x <= x_right)
    {
        f = false;
        while (img->pixelColor(x, y) != border_color &&
               img->pixelColor(x, y) != fill_color &&
               x <= x_right)
        {
            if (f == false)
                f = true;
            x++;
        }
        if (f == true)
        {
            if (x == x_right && img->pixelColor(x, y) != border_color &&
                    img->pixelColor(x, y) != fill_color)
                stack->push_back(QPoint (x, y));
            else
                stack->push_back(QPoint(x - 1, y));
            f = false;
        }
        xn = x;
        while ((img->pixelColor(x, y) == border_color ||
               img->pixelColor(x, y) == fill_color) &&
               x != x_right)
            x++;
        if (x == xn)
            x++;
    }
}

void filling(QImage *img, QGraphicsScene *scene,
             QColor border_color, QColor fill_color, QColor bg_color, int x, int y, bool delay)
{
    QVector <QPoint> stack;
    stack.push_back(QPoint(x, y));
    while (stack.size() != 0)
    {
        QPoint a = stack.back();
        stack.pop_back();
        int x = a.x();
        int y = a.y();
        img->setPixelColor(x, y, fill_color);
        int wx = x;
        x++;
        while (img->pixelColor(x, y) != border_color)
        {
            img->setPixelColor(x, y, fill_color);
            x++;
        }
        int x_right = x - 1;
        x = wx;
        x--;
        while (img->pixelColor(x, y) != border_color)
        {
            img->setPixelColor(x, y, fill_color);
            x--;
        }
        int x_left = x + 1;
        find_new_pixel(img, scene, border_color, fill_color,
                       bg_color, &stack, y + 1, x_right, x_left);
        find_new_pixel(img, scene, border_color, fill_color,
                       bg_color, &stack, y - 1, x_right, x_left);
        if (delay)
        {
            scene->clear();
            scene->addPixmap(QPixmap::fromImage(*img));
            QTime dieTime = QTime::currentTime().addMSecs(delay);
            while(QTime::currentTime() < dieTime)
                QCoreApplication::processEvents(QEventLoop::AllEvents,
                                                delay);
        }
    }
}
