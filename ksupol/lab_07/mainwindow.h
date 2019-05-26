#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "paint.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QColor>
#include <QVector>
#include <QComboBox>
#include <QRadioButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QComboBox *col_b;
    QComboBox *col_f;

public:
    explicit MainWindow(QImage *image, QVector<QLine> *segments,
                        Paint *p,
                        QWidget *parent = nullptr);
    ~MainWindow();
    bool line_or_clipper = true;
    int h;
    int w;

    void add_scene(QGraphicsScene *scene);
    void insert_into_table(QString x, QString y);

private slots:

    void on_inputLine_clicked();
    void on_pushButton_clicked();
    void on_lineColor_currentIndexChanged(int index);
    void on_clipper_clicked();
    void on_line_clicked();
    void on_clipperColor_currentIndexChanged(int index);
    void on_setClipper_clicked();

private:
    Ui::MainWindow *ui;

    Paint *paint;
    QImage *img;
    QVector<QLine> *lines;
};
#endif // MAINWINDOW_H
