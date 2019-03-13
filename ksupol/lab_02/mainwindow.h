#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "draw.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    float *x_cir_1 = NULL;
    float *x_cir_2 = NULL;
    float *y_cir_1 = NULL;
    float *y_cir_2 = NULL;

    float *x_par_1 = NULL;
    float *x_par_2 = NULL;
    float *y_par_1 = NULL;
    float *y_par_2 = NULL;

    int a_cir_x = 0;
    int a_cir_y = 0;
    int a_par_x = 0;
    int a_par_y = 0;
    int action = 0;

    float *x_c_1 = NULL;
    float *x_c_2 = NULL;
    float *y_c_1 = NULL;
    float *y_c_2 = NULL;

    float *x_p_1 = NULL;
    float *x_p_2 = NULL;
    float *y_p_1 = NULL;
    float *y_p_2 = NULL;

private slots:
    void on_move_clicked();

    void on_rotate_clicked();

    void on_scale_clicked();

    void on_back_clicked();

    void on_start_clicked();

    void change_move(float x, float y);
    void change_rotate(int d, float x, float y, float de);
    void change_scale(float kx, float ky, float x, float y);

    void draw_obj();
    void draw_obj_sc();
    void save_changes();


private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
};

#endif // MAINWINDOW_H
