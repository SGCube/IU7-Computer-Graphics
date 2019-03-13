#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "check.h"
#include "draw.h"
#include <stdlib.h>
#include <QMessageBox>
#include <QGraphicsScene>
#include <qmath.h>
#include <QString>
#include <QDebug>
#define a 315
#define b 335
#define r 30
#define c 20
#define d 100

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Лабораторная работа №2");

    scene = new QGraphicsScene(this);
    ui->graphics->setScene(scene);

    ui->graphics->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphics->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QPen blueBrush(Qt::blue);
    QPen blackpen(Qt::black);
    blackpen.setWidth(1);
    blueBrush.setWidth(1);
    QBrush blBrush(Qt::black);

    a_cir_x = (r + r) / 0.05 + 1;
    a_cir_y = a_cir_x;
    x_cir_1 = (float *)calloc(a_cir_x, sizeof(float));
    x_cir_2 = (float *)calloc(a_cir_x, sizeof(float));
    y_cir_1 = (float *)calloc(a_cir_y, sizeof(float));
    y_cir_2 = (float *)calloc(a_cir_y, sizeof(float));
    float y;
    int i = 0;

    for (float x = -r; x <= r; x += 0.05)
    {
        y = sqrt(qPow(r, 2) - qPow(x, 2));
        x_cir_1[i] = x + a;
        x_cir_2[i] = x + a;
        y_cir_1[i] = y + b;
        y_cir_2[i] = b - y;
        i++;
    }
    for (int i = 0; i < a_cir_x; i++)
    {
        scene->addEllipse(x_cir_1[i], y_cir_1[i], 3, 3, blackpen, blBrush);
        scene->addEllipse(x_cir_2[i], y_cir_2[i], 3, 3, blackpen, blBrush);
    }

    a_par_x = (c + d) / 0.05;
    a_par_y = a_par_x;
    x_par_1 = (float *)calloc(a_par_x, sizeof(float));
    x_par_2 = (float *)calloc(a_par_x, sizeof(float));
    y_par_1 = (float *)calloc(a_par_y, sizeof(float));
    y_par_2 = (float *)calloc(a_par_y, sizeof(float));
    i = 0;
    for (float x = -c; x <= d; x += 0.05)
    {
        y = sqrt(x + c);
        x_par_1[i] = x + a;
        x_par_2[i] = x + a;
        y_par_1[i] = y + b;
        y_par_2[i] = b - y;
        i++;
    }
    for (int i = 0; i < a_par_x; i++)
    {
        scene->addEllipse(x_par_1[i], y_par_1[i], 3, 3, blackpen, blBrush);
        scene->addEllipse(x_par_2[i], y_par_2[i], 3, 3, blackpen, blBrush);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete x_cir_1;
    delete x_cir_2;
    delete y_cir_1;
    delete y_cir_2;
    delete x_par_1;
    delete x_par_2;
    delete y_par_1;
    delete y_par_2;

    delete x_c_1;
    delete x_c_2;
    delete y_c_1;
    delete y_c_2;
    delete x_p_1;
    delete x_p_2;
    delete y_p_1;
    delete y_p_2;
}

void MainWindow::on_move_clicked()
{
    int check = 0;
    QString x = ui->moveX->text();
    QString y = ui->moveY->text();
    if (x == NULL && y == NULL)
    {
        QMessageBox::warning(this, "Ошибка", "Заполните необходимые поля!");
        return;
    }
    check = check_point(x);
    if (check != 0)
    {
        QMessageBox::warning(this, "Ошибка", "Введите корректную координату X!");
        return;
    }
    check = check_point(y);
    if (check != 0)
    {
        QMessageBox::warning(this, "Ошибка", "Введите корректную координату Y!");
        return;
    }
    float xx = x.toFloat();
    float yy = y.toFloat();
    change_move(xx, yy);
    draw_obj();
    action = 1;
}

void MainWindow::on_rotate_clicked()
{
    QString rot = ui->rot->text();
    QString rotX = ui->rotX->text();
    QString rotY = ui->rotY->text();
    int check = 0;

    if (rot == NULL && rotX == NULL && rotY == NULL)
    {
        QMessageBox::warning(this, "Ошибка", "Заполните необходимые поля!");
        return;
    }
    if (rot == NULL)
    {
        QMessageBox::warning(this, "Ошибка", "Введите угол!");
        return;
    }
    if (rotX == NULL && rotY == NULL)
    {
        QMessageBox::warning(this, "Ошибка", "Введите координаты центра поворота!");
        return;
    }
    if (rotX == NULL)
    {
        QMessageBox::warning(this, "Ошибка", "Введит координату X!");
        return;
    }
    if (rotY == NULL)
    {
        QMessageBox::warning(this, "Ошибка", "Введит координату Y!");
        return;
    }
    check = check_point(rot);
    if (check != 0)
    {
        QMessageBox::warning(this, "Ошибка", "Введите корректный угол!");
        return;
    }
    check = check_point(rotX);
    if (check != 0)
    {
        QMessageBox::warning(this, "Ошибка", "Введите корректную координату X!");
        return;
    }
    check = check_point(rotY);
    if (check != 0)
    {
        QMessageBox::warning(this, "Ошибка", "Введите корректную координату Y!");
        return;
    }
    float x = rotX.toFloat();
    float y = rotY.toFloat();
    float deg = rot.toFloat();
    if (ui->deg->isChecked())
        change_rotate(0, x, y, deg);
    else
        change_rotate(1, x, y, deg);
    draw_obj();
    QString text = "поворота";
    draw_center(x, y, text, scene);
    action = 2;
}

void MainWindow::on_scale_clicked()
{
    QString kx = ui->kx->text();
    QString ky = ui->ky->text();
    QString scaleX = ui->scaleX->text();
    QString scaleY = ui->scaleY->text();

    if (kx == NULL)
    {
        QMessageBox::warning(this, "Ошибка", "Введите коэффициент X!");
        return;
    }
    if (ky == NULL)
    {
        QMessageBox::warning(this, "Ошибка", "Введите коэффициент Y!");
        return;
    }
    if (scaleX == NULL)
    {
        QMessageBox::warning(this, "Ошибка", "Введите координату X!");
        return;
    }
    if (scaleY == NULL)
    {
        QMessageBox::warning(this, "Ошибка", "Введите координату Y!");
        return;
    }
    int check = 0;
    check = check_point(kx);
    if (check != 0)
    {
        QMessageBox::warning(this, "Ошибка", "Введите корректный коэффициент X!");
        return;
    }
    float kkx = kx.toFloat();
    check = check_point(ky);
    if (check != 0)
    {
        QMessageBox::warning(this, "Ошибка", "Введите корректный коэффициент Y!");
        return;
    }
    float kky = ky.toFloat();
    check = check_point(scaleX);
    if (check != 0)
    {
        QMessageBox::warning(this, "Ошибка", "Введите корректную координату X!");
        return;
    }
    check = check_point(scaleY);
    if (check != 0)
    {
        QMessageBox::warning(this, "Ошибка", "Введите корректную координату Y!");
        return;
    }
    float x = scaleX.toFloat();
    float y = scaleY.toFloat();
    if (kkx == 0 || kky == 0)
        save_changes();
    change_scale(kkx, kky, x, y);
    draw_obj();
    QString text = "масштабирования";
    draw_center(x, y, text, scene);
    action = 3;
}

void MainWindow::on_back_clicked()
{
    if (action == 1)
    {
        QString xx = ui->moveX->text();
        QString yy = ui->moveY->text();
        float x = xx.toFloat();
        float y = yy.toFloat();
        change_move(-x, -y);
        draw_obj();
    }
    if (action == 2)
    {
        QString xx = ui->rotX->text();
        QString yy = ui->rotY->text();
        QString de = ui->rot->text();
        float x = xx.toFloat();
        float y = yy.toFloat();
        float deg = de.toFloat();
        if (ui->deg->isChecked())
            change_rotate(0, x, y, -deg);
        else
            change_rotate(1, x, y, -deg);
        draw_obj();
    }
    if (action == 3)
    {
        QString kx = ui->kx->text();
        QString ky = ui->ky->text();
        QString scaleX = ui->scaleX->text();
        QString scaleY = ui->scaleY->text();
        float kkx = kx.toFloat();
        float kky = ky.toFloat();
        float x = scaleX.toFloat();
        float y = scaleY.toFloat();
        if (kkx == 0 || kky == 0)
            draw_obj_sc();
        else
        {
            change_scale(1/kkx, 1/kky, x, y);
            draw_obj();
        }

    }
    action = 4;
}

void MainWindow::change_move(float x, float y)
{
    for (int i = 0; i < a_cir_x; i++)
    {
        x_cir_1[i] += x;
        x_cir_2[i] += x;
    }
    for (int i = 0; i < a_cir_y; i++)
    {
        y_cir_1[i] += y;
        y_cir_2[i] += y;
    }
    for (int i = 0; i < a_par_x; i++)
    {
        x_par_1[i] += x;
        x_par_2[i] += x;
    }
    for (int i = 0; i < a_par_y; i++)
    {
        y_par_1[i] += y;
        y_par_2[i] += y;
    }
}

void MainWindow::change_rotate(int dd, float xc, float yc, float de)
{
    scene->clear();
    QPen blueBrush(Qt::blue);
    QPen blackpen(Qt::black);
    blackpen.setWidth(1);
    blueBrush.setWidth(1);
    QBrush blBrush(Qt::black);

    float rad;
    if (dd == 0)
        rad = qDegreesToRadians(de) * -1;
    else
        rad = de * -1;

    for (int i = 0; i < a_cir_x; i++)
    {
        float x = xc + (x_cir_1[i] - xc)*cos(rad) - (y_cir_1[i] - yc)*sin(rad);
        float y = yc + (y_cir_1[i] - yc)*cos(rad) + (x_cir_1[i] - xc)*sin(rad);
        x_cir_1[i] = x;
        y_cir_1[i] = y;
    }
    for (int i = 0; i < a_cir_x; i++)
    {
        float x = xc + (x_cir_2[i] - xc)*cos(rad) - (y_cir_2[i] - yc)*sin(rad);
        float y = yc + (y_cir_2[i] - yc)*cos(rad) + (x_cir_2[i] - xc)*sin(rad);
        x_cir_2[i] = x;
        y_cir_2[i] = y;
    }
    for (int i = 0; i < a_par_x; i++)
    {
        float x = xc + (x_par_1[i] - xc)*cos(rad) - (y_par_1[i] - yc)*sin(rad);
        float y = yc + (y_par_1[i] - yc)*cos(rad) + (x_par_1[i] - xc)*sin(rad);
        x_par_1[i] = x;
        y_par_1[i] = y;
    }
    for (int i = 0; i < a_par_x; i++)
    {
        float x = xc + (x_par_2[i] - xc)*cos(rad) - (y_par_2[i] - yc)*sin(rad);
        float y = yc + (y_par_2[i] - yc)*cos(rad) + (x_par_2[i] - xc)*sin(rad);
        x_par_2[i] = x;
        y_par_2[i] = y;
    }
}

void MainWindow::change_scale(float kx, float ky, float x, float y)
{
    for (int i = 0; i < a_cir_x; i++)
    {
        x_cir_1[i] = kx * x_cir_1[i] + (1 - kx) * x;
        x_cir_2[i] = kx * x_cir_2[i] + (1 - kx) * x;
    }
    for (int i = 0; i < a_cir_y; i++)
    {
        y_cir_1[i] =  y_cir_1[i] * ky + y * (1 - ky);
        y_cir_2[i] =  y_cir_2[i] * ky + y * (1 - ky);
    }
    for (int i = 0; i < a_par_x; i++)
    {
        x_par_1[i] = kx * x_par_1[i] + (1 - kx) * x;
        x_par_2[i] = kx * x_par_2[i] + (1 - kx) * x;
    }
    for (int i = 0; i < a_par_y; i++)
    {
        y_par_1[i] =  y_par_1[i] * ky + y * (1 - ky);
        y_par_2[i] =  y_par_2[i] * ky + y * (1 - ky);
    }
}

void MainWindow::draw_obj()
{
    QPen blueBrush(Qt::blue);
    QPen blackpen(Qt::black);
    blackpen.setWidth(1);
    blueBrush.setWidth(1);
    QBrush blBrush(Qt::black);

    scene->clear();
    for (int i = 0; i < a_cir_x; i++)
        scene->addEllipse(x_cir_1[i], y_cir_1[i], 3, 3, blackpen, blBrush);
    for (int i = 0; i < a_cir_y; i++)
        scene->addEllipse(x_cir_2[i], y_cir_2[i], 3, 3, blackpen, blBrush);

    for (int i = 0; i < a_par_x; i++)
        scene->addEllipse(x_par_1[i], y_par_1[i], 3, 3, blackpen, blBrush);
    for (int i = 0; i < a_par_y; i++)
        scene->addEllipse(x_par_2[i], y_par_2[i], 3, 3, blackpen, blBrush);
}

void MainWindow::on_start_clicked()
{
    float y;
    int i = 0;
    for (float x = -r; x <= r; x += 0.05)
    {
        y = sqrt(qPow(r, 2) - qPow(x, 2));
        x_cir_1[i] = x + a;
        x_cir_2[i] = x + a;
        y_cir_1[i] = y + b;
        y_cir_2[i] = b - y;
        i++;
    }
    i = 0;
    for (float x = -c; x <= d; x += 0.05)
    {
        y = sqrt(x + c);
        x_par_1[i] = x + a;
        x_par_2[i] = x + a;
        y_par_1[i] = y + b;
        y_par_2[i] = b - y;
        i++;
    }
    draw_obj();
}

void MainWindow::save_changes()
{
    x_c_1 = (float *)calloc(a_cir_x, sizeof(float));
    x_c_2 = (float *)calloc(a_cir_x, sizeof(float));
    y_c_1 = (float *)calloc(a_cir_y, sizeof(float));
    y_c_2 = (float *)calloc(a_cir_y, sizeof(float));

    x_p_1 = (float *)calloc(a_par_x, sizeof(float));
    x_p_2 = (float *)calloc(a_par_x, sizeof(float));
    y_p_1 = (float *)calloc(a_par_y, sizeof(float));
    y_p_2 = (float *)calloc(a_par_y, sizeof(float));

    for (int i = 0; i < a_cir_x; i++)
    {
        x_c_1[i] = x_cir_1[i];
        x_c_2[i] = x_cir_2[i];
    }
    for (int i = 0; i < a_cir_y; i++)
    {
        y_c_1[i] = y_cir_1[i];
        y_c_2[i] = y_cir_2[i];
    }
    for (int i = 0; i < a_par_x; i++)
    {
        x_p_1[i] = x_par_1[i];
        x_p_2[i] = x_par_2[i];
    }
    for (int i = 0; i < a_par_y; i++)
    {
        y_p_1[i] = y_par_1[i];
        y_p_2[i] = y_par_2[i];
    }
}

void MainWindow::draw_obj_sc()
{
    QPen blueBrush(Qt::blue);
    QPen blackpen(Qt::black);
    blackpen.setWidth(1);
    blueBrush.setWidth(1);
    QBrush blBrush(Qt::black);

    scene->clear();
    for (int i = 0; i < a_cir_x; i++)
        scene->addEllipse(x_c_1[i], y_c_1[i], 3, 3, blackpen, blBrush);
    for (int i = 0; i < a_cir_y; i++)
        scene->addEllipse(x_c_2[i], y_c_2[i], 3, 3, blackpen, blBrush);

    for (int i = 0; i < a_par_x; i++)
        scene->addEllipse(x_p_1[i], y_p_1[i], 3, 3, blackpen, blBrush);
    for (int i = 0; i < a_par_y; i++)
        scene->addEllipse(x_p_2[i], y_p_2[i], 3, 3, blackpen, blBrush);
}
