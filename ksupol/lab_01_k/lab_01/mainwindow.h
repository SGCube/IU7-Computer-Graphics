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
    float x2;
    float y2;
    float x3;
    float y3;
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
    int check_point(QString );
    void insert_into_table(QString x, QString y);
    point *add_to_list(point *head, float a, float b);
    void on_change_clicked();
    void clear_list();
    void clear_list_res();
    point *change_element(point *head, int a_int, QString new_x, QString new_y);
    point *delete_from_list(point *head, int d);
    void on_delet_clicked();

    void on_delete_all_clicked();

    void on_show_clicked();
    void find_result();
    int check_tr(float x1, float y1, float x2, float y2, float x3, float y3);
    float diff(float x1, float y1, float x2, float y2, float x3, float y3);
    tri *insert_in_res(tri *head_res, float x1, float y1,
                                     float x2, float y2, float x3, float y3);
    void draw_result(tri *head_res);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rectangle;
    point *head = NULL;
    tri *head_res = NULL;
    int amount = 0;
};

#endif // MAINWINDOW_H
