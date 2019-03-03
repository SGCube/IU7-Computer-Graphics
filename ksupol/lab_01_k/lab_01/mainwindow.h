#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>

typedef struct p point;
struct p {
    float x;
    float y;
    point *next;
};

typedef struct triangle tri;
struct triangle {
    float x1;
    float y1;
    int num1;
    float x2;
    float y2;
    int num2;
    float x3;
    float y3;
    int num3;
    tri *next;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_enter_clicked();
    void insert_into_table(QString x, QString y);
    void on_change_clicked();
    void change_table(int a_int, QString new_x, QString new_y);
    void on_delet_clicked();

    void on_delete_all_clicked();

    void on_show_clicked();
    void find_result();
    float diff(float x1, float y1, float x2, float y2, float x3, float y3);
    void draw_result(tri *head_res);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rectangle;
    QGraphicsTextItem *l1;
};

#endif // MAINWINDOW_H
