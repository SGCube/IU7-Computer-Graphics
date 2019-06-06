﻿#include "mainwindow.h"
#include "draw_ar.h"
#include "paint.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QImage img(860, 660, QImage::Format_RGB32);
    img.fill(QColor(255, 255, 255));
    Paint paint;
    QVector<QVector<QPoint>> polygons_kit;
    QVector<QPoint> pol;


    MainWindow w(&img, &polygons_kit, &pol, &paint);
    Draw_ar scene(&img, &paint, &polygons_kit, &pol, &w);
    w.add_scene(&scene);

    w.show();

    return a.exec();
}