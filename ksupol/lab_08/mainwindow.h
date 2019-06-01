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
    explicit MainWindow(QImage *image, QVector<QLine> *segments, QVector<QPoint> *cutter,
                        Paint *p,
                        QWidget *parent = nullptr);
    ~MainWindow();
    bool line_or_clipper = true;
    bool set_clipper = false;
    void add_scene(QGraphicsScene *scene);
    /*
    void insert_into_table_lines(QString x, QString y);
    void insert_into_table_clipper(QString x, QString y);
    */

private slots:
    /*
    void on_inputLine_clicked();
    void on_clear_clicked();
    void on_lineColor_currentIndexChanged(int index);
    void on_clipper_clicked();
    void on_line_clicked();
    void on_clipperColor_currentIndexChanged(int index);
    */

private:
    Ui::MainWindow *ui;

    Paint *paint;
    QImage *img;
    QVector<QLine> *lines;
    QVector<QPoint> *clipper;
};
#endif // MAINWINDOW_H
