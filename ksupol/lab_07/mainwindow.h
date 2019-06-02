#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "paint.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QColor>
#include <QVector>
#include <QComboBox>
#include <QRadioButton>
#include <QTextBrowser>

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
    bool line_or_clipper = true;
    int h;
    int w;
    bool set_clipper = false;
    void add_scene(QGraphicsScene *scene);
    void insert_into_table(QString x, QString y);
    QTextBrowser *text;

private slots:

    void on_inputLine_clicked();
    void on_pushButton_clicked();
    void on_lineColor_currentIndexChanged(int index);
    void on_clipper_clicked();
    void on_line_clicked();
    void on_clipperColor_currentIndexChanged(int index);
    void on_setClipper_clicked();
    void on_clip_clicked();
    void lineCodes(QLine line, unsigned char *t1, unsigned char *t2, int *s1, int *s2);
    void put_line(QPoint r1, QPoint r2, bool pr);
    void a(int *j, QPoint r1, QPoint r2, QVector<int> *clipper, bool pr, QPoint q, QLine line, float m);

private:
    Ui::MainWindow *ui;

    Paint *paint;
    QImage *img;
    QVector<QLine> *lines;
    QVector<int> *clipper;
};
#endif // MAINWINDOW_H
