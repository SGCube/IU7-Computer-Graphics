#include "mainwindow.h"
#include "paint.h"
#include "draw_ar.h"
#include <QApplication>
#include <QGraphicsScene>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QImage img(800, 700, QImage::Format_RGB32);
    img.fill(QColor(255, 255, 255));
    Paint paint;
    QVector<QLine> lines;
    QVector<int> clipper;

    MainWindow w(&img, &lines, &clipper, &paint);
    Draw_ar scene(&img, &paint, &lines, &clipper, &w);
    w.add_scene(&scene);

    w.show();

    return a.exec();
}
