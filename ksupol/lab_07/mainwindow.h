﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "paint.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QColor>
#include <QVector>
#include <QComboBox>
#include <QRadioButton>
#include <QTextBrowser>

#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QComboBox *col_b;
    QComboBox *col_f;

public:
    explicit MainWindow(QImage *image, QVector<QLine> *segments, QVector<int> *cutter,
                        Paint *p,
                        QWidget *parent = nullptr);
    ~MainWindow();
    bool line = true;
    bool set_clipper = false;
    void add_scene(QGraphicsScene *scene);
    void insert_into_table(QString x, QString y);
    QTextBrowser *text;

private slots:

    void on_inputLine_clicked();
    void on_clear_clicked();
    void on_lineColor_currentIndexChanged(int index);
    void on_clipperColor_currentIndexChanged(int index);
    void on_clipper_clicked();
    void on_line_clicked();
    void on_clip_clicked();
    void clip_line(int i);
    void pointCode(QPoint a, unsigned char *t);
    void put_line(QPoint r1, QPoint r2);
    int check_visibility(unsigned char t1, unsigned char t2);
    void on_resultColor_currentIndexChanged(int index);

    void checkPointPosition(QPoint res1, QPoint res2, float m, QPoint p);
    bool find_bottom_crossing(QPoint res1, QPoint res2, QPoint p2, float m);
    bool find_top_crossing(QPoint res1, QPoint res2, QPoint p2, float m);
    bool find_left_crossing(QPoint res1, QPoint res2, QPoint p2, float m);
    bool find_right_crossing(QPoint res1, QPoint res2, QPoint p2, float m);
    /*
    void a(QPoint p1, QPoint p2, QPoint p, float m, int flag, int *j);
    void b(QPoint p1, QPoint p2, QPoint p, float m, int flag, int *j);
    void c(QPoint p1, QPoint p2, QPoint p, float m, int flag, int *j);
    void d(QPoint p1, QPoint p2, QPoint p, float m, int flag, int *j);
    void e(QPoint p1, QPoint p2, QPoint p, float m, int flag, int *j);
    void f(QPoint p1, QPoint p2, int flag);
    */

private:
    Ui::MainWindow *ui;

    Paint *paint;
    QImage *img;
    QVector<QLine> *lines;
    QVector<int> *clipper;
};
#endif // MAINWINDOW_H