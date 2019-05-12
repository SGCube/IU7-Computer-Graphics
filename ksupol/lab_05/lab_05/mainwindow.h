#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QColor>

#include "paint.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    int check_b = 0;

public:
    explicit MainWindow(QImage *image, Paint *p, QWidget *parent = 0);
    ~MainWindow();

    void add_scene(QGraphicsScene *scene);

private slots:
    void on_add_point_clicked();
    void insert_into_table(QString x, QString y);

    void on_clear_clicked();

    void on_lock_clicked();

    void on_clear_table_clicked();

private:
    Ui::MainWindow *ui;

    Paint *paint;
    QImage *img;

    QVector<QPoint> polygon;
    QVector<QVector<QPoint>> *polygons;
    QPen pen;
    QColor *col;

};

#endif // MAINWINDOW_H
