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

struct vector
{
    int x;
    int y;
    int z;
    vector() {}
    vector(int tx, int ty, int tz = 0)
    {
        x = tx;
        y = ty;
        z = tz;
    }
    vector(QPoint p2, QPoint p1)
    {
        x = p2.x() - p1.x();
        y = p2.y() - p1.y();
        z = 0;
    }
    vector(QLine line)
    {
        x = line.x2() - line.x1();
        y = line.y2() - line.y1();
        z = 0;
    }
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QComboBox *col_b;
    QComboBox *col_f;
    int direction;

public:
    explicit MainWindow(QImage *image, QVector<QLine> *segments, QVector<QPoint> *cutter,
                        Paint *p,
                        QWidget *parent = nullptr);
    ~MainWindow();
    bool line = true;
    bool set_clipper = false;
    void add_scene(QGraphicsScene *scene);
    void insert_into_table_lines(QString x, QString y);
    void insert_into_table_clipper(QString x, QString y);

private slots:

    void on_inputLine_clicked();
    void on_clear_clicked();
    void on_lineColor_currentIndexChanged(int index);
    void on_clipper_clicked();
    void on_line_clicked();
    void on_clipperColor_currentIndexChanged(int index);

    void on_inputClipper_clicked();

    void on_clip_clicked();
    bool is_convex();
    QVector<QLine> from_points_to_lines();
    void calculate_normals();
    void cut_line(int i);
    void draw_result();

    void on_resultColor_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;

    Paint *paint;
    QImage *img;
    QVector<QLine> *lines;
    QVector<QPoint> *clipper;
    QVector<QLine> cutter;
    QVector<vector> normals;
    QVector<QLine> result;
};
#endif // MAINWINDOW_H
