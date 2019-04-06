#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "check.h"
#include "draw.h"
#include <QMessageBox>
#include <QDebug>
#include <QtMath>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Лабораторная работа №3");

    scene = new QGraphicsScene(this);
    ui->graphics->setScene(scene);

    ui->graphics->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphics->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_build_clicked()
{
    QString startX = ui->startX->text();
    QString startY = ui->startY->text();
    QString endX = ui->endX->text();
    QString endY = ui->endY->text();
    if (startX == NULL)
    {
        QMessageBox::critical(this, "Ошибка", "Введите координату X для начала отрезка!");
        return;
    }
    if (startY == NULL)
    {
        QMessageBox::critical(this, "Ошибка", "Введите координату y для начала отрезка!");
        return;
    }
    if (endX == NULL)
    {
        QMessageBox::critical(this, "Ошибка", "Введите координату X для конца отрезка!");
        return;
    }
    if (endY == NULL)
    {
        QMessageBox::critical(this, "Ошибка", "Введите координату Y для конца отрезка!");
        return;
    }
    int check = check_point(startX);
    if (check != 0)
    {
        QMessageBox::critical(this, "Ошибка", "Введите корректную"
                                            " координату X для начала отрезка!");
        return;
    }
    check = check_point(startY);
    if (check != 0)
    {
        QMessageBox::critical(this, "Ошибка", "Введите корректную"
                                            " координату Y для начала отрезка!");
        return;
    }
    check = check_point(endX);
    if (check != 0)
    {
        QMessageBox::critical(this, "Ошибка", "Введите корректную"
                                            " координату Y для начала отрезка!");
        return;
    }
    check = check_point(endY);
    if (check != 0)
    {
        QMessageBox::critical(this, "Ошибка", "Введите корректную"
                                            " координату Y для начала отрезка!");
        return;
    }
    if (startX == endX && startY == endY)
    {
        QMessageBox::critical(this, "Ошибка", "Отрезок вырожден!");
        return;
    }
    float sX = startX.toFloat();
    float sY = startY.toFloat();
    float eX = endX.toFloat();
    float eY = endY.toFloat();
    int alg = ui->algor->currentIndex();
    int col = ui->colour->currentIndex();
    int bgc_col = ui->bgc->isChecked();
    if (alg == 0)
        draw_dda(sX, sY, eX, eY, col, bgc_col, scene);
    if (alg == 1)
        draw_real(sX, sY, eX, eY, col, bgc_col, scene);
    if (alg == 2)
        draw_int(sX, sY, eX, eY, col, bgc_col, scene);
    if (alg == 3)
        draw_step(sX, sY, eX, eY, col, bgc_col, scene);
    if (alg == 4)
        draw_library(sX, sY, eX, eY, col, bgc_col, scene);
}

void MainWindow::on_build_sp_clicked()
{
    QString deg = ui->deg->text();
    if (deg == NULL)
    {
        QMessageBox::critical(this, "Ошибка", "Введите угол!");
        return;
    }
    int check = check_point(deg);
    if (check != 0)
    {
        QMessageBox::critical(this, "Ошибка", "Введите корректный угол!");
        return;
    }
    int bgc_col = ui->bgc_2->isChecked();
    int alg = ui->algor_2->currentIndex();
    int col = ui->colour_2->currentIndex();
    float degr = deg.toFloat();
    draw_spectrum(col, bgc_col, alg, degr, scene);
}

void MainWindow::on_pushButton_clicked()
{
    scene->clear();
}
