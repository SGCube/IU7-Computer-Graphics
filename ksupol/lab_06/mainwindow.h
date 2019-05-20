#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QColor>
#include <QVector>
#include <QComboBox>

#include "paint.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    int check_b = 0;
    QComboBox *col_b;
    QComboBox *col_f;

public:
    explicit MainWindow(QImage *image, QVector<QVector<QPoint>> *polygons, QVector<QPoint> *pol,
                        Paint *p,
                        QWidget *parent = nullptr);
    ~MainWindow();

    void add_scene(QGraphicsScene *scene);
    void insert_into_table(QString x, QString y);
    void insert_pixel(int xx, int yy);

private slots:
    void on_add_point_clicked();

    void on_clear_clicked();

    void on_lock_clicked();

    void on_fill_clicked();

    void on_col_b_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;

    Paint *paint;
    QImage *img;

    QVector<QPoint> *polygon;
    QVector<QVector<QPoint>> *polygons_kit;
    int x = 0, y = 0;
};
#endif // MAINWINDOW_H
