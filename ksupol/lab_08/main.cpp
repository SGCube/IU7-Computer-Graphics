#include "mainwindow.h"
#include "draw_ar.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QImage img(860, 660, QImage::Format_RGB32);
    img.fill(QColor(255, 255, 255));
    Paint paint;
    QVector<QLine> lines;
    QVector<QPoint> clipper;

    MainWindow w(&img, &lines, &clipper, &paint);
    Draw_ar scene(&img, &paint, &lines, &clipper, &w);
    w.add_scene(&scene);

    return a.exec();
}
