#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "check.h"
#include "draw_circle.h"
#include "draw_ellipse.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Лабораторная работа №4");

    scene = new QGraphicsScene(this);
    ui->graphics->setScene(scene);

    ui->graphics->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphics->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_cir_build_clicked()
{
    double x;
    double y;
    int check;
    QString cor_x = ui->cir_x->text();
    QString cor_y = ui->cir_y->text();
    if ((cor_x == NULL && cor_y != NULL) || (cor_y == NULL && cor_x != NULL))
    {
        QMessageBox::critical(this, "Ошибка", "Заполните координаты центра!");
        return;
    }
    if (cor_x == NULL && cor_y == NULL)
    {
        x = 0;
        y = 0;
    }
    else
    {
        check = check_point(cor_x);
        if (check != 0)
        {
            QMessageBox::critical(this, "Ошибка", "Введите корректную координату X!");
            return;
        }
        check = check_point(cor_y);
        if (check != 0)
        {
            QMessageBox::critical(this, "Ошибка", "Введите корректную координату Y!");
            return;
        }
        x = cor_x.toFloat();
        y = cor_y.toFloat();
    }
    QString rad = ui->cir_r->text();
    if (rad == NULL)
    {
        QMessageBox::critical(this, "Ошибка", "Введите радиус окружности!");
        return;
    }
    check = check_point(rad);
    if (check != 0)
    {
        QMessageBox::critical(this, "Ошибка", "Введите корректный радиус!");
        return;
    }
    double r = rad.toFloat();
    int alg = ui->cir_alg->currentIndex();
    int col = ui->cir_col->currentIndex();
    int bgc_col = ui->cir_bgc->isChecked();
    c = new QColor;
    set_colour(bgc_col, col, c);
    if (alg == 0)
        draw_kanon(x, y, r, c, scene);
    if (alg == 1)
        draw_param(x, y, r, c, scene);
    if (alg == 2)
        draw_bres(x, y, r, c, scene);
    if (alg == 3)
        draw_mid(x, y, r, c, scene);
    if (alg == 4)
        draw_library(x, y, r, c, scene);
}

void MainWindow::on_pushButton_2_clicked()
{
    scene->clear();
}

void MainWindow::on_cir_build_2_clicked()
{
    QString st_r = ui->cir_st_r->text();
    if (st_r == NULL)
    {
        QMessageBox::critical(this, "Ошибка", "Введите начальный радиус!");
        return;
    }
    int check = check_point(st_r);
    if (check != 0)
    {
        QMessageBox::critical(this, "Ошибка", "Введите корректный начальный радиус!");
        return;
    }
    QString end_r = ui->cir_end_r->text();
    if (end_r == NULL)
    {
        QMessageBox::critical(this, "Ошибка", "Введите конечный радиус!");
        return;
    }
    check = check_point(end_r);
    if (check != 0)
    {
        QMessageBox::critical(this, "Ошибка", "Введите корректный конечный радиус!");
        return;
    }
    QString kol = ui->cir_am->text();
    if (kol == NULL)
    {
        QMessageBox::critical(this, "Ошибка", "Введите количество окружностей!");
        return;
    }
    check = check_point(kol);
    if (check != 0)
    {
        QMessageBox::critical(this, "Ошибка", "Введите корректное количество окружностей!");
        return;
    }
    int s_r = st_r.toInt();
    int e_r = end_r.toInt();
    if (e_r < s_r)
    {
        QMessageBox::critical(this, "Ошибка", "Начальный радиус больше конечного!");
        return;
    }
    if (e_r < 0 || s_r < 0)
    {
        QMessageBox::critical(this, "Ошибка", "Радиус не может быть отрицательным!");
        return;
    }
    int k = kol.toInt();
    if (k < 0)
    {
        QMessageBox::critical(this, "Ошибка", "Количество окружностей не может быть отрицательным!");
        return;
    }
    int alg = ui->cir_alg_2->currentIndex();
    int col = ui->cir_col_2->currentIndex();
    int bgc_col = ui->cir_bgc_2->isChecked();
    c = new QColor;
    set_colour(bgc_col, col, c);
    draw_cir_spectr(s_r, e_r, k, c, scene, alg);
}

void MainWindow::on_el_build_clicked()
{
    double x;
    double y;
    int check;
    QString cor_x = ui->el_x->text();
    QString cor_y = ui->el_y->text();
    if ((cor_x == NULL && cor_y != NULL) || (cor_y == NULL && cor_x != NULL))
    {
        QMessageBox::critical(this, "Ошибка", "Заполните координаты центра!");
        return;
    }
    if (cor_x == NULL && cor_y == NULL)
    {
        x = 0;
        y = 0;
    }
    else
    {
        check = check_point(cor_x);
        if (check != 0)
        {
            QMessageBox::critical(this, "Ошибка", "Введите корректную координату X!");
            return;
        }
        check = check_point(cor_y);
        if (check != 0)
        {
            QMessageBox::critical(this, "Ошибка", "Введите корректную координату Y!");
            return;
        }
        x = cor_x.toFloat();
        y = cor_y.toFloat();
    }
    QString aa = ui->el_a->text();
    if (aa == NULL)
    {
        QMessageBox::critical(this, "Ошибка", "Введите большую ось эллипса!");
        return;
    }
    check = check_point(aa);
    if (check != 0)
    {
        QMessageBox::critical(this, "Ошибка", "Введите корректную большую ось эллипса!");
        return;
    }
    double a = aa.toFloat();

    QString bb = ui->el_b->text();
    if (bb == NULL)
    {
        QMessageBox::critical(this, "Ошибка", "Введите малую ось эллипса!");
        return;
    }
    check = check_point(bb);
    if (check != 0)
    {
        QMessageBox::critical(this, "Ошибка", "Введите корректную малую ось эллипса!");
        return;
    }
    double b = bb.toFloat();

    int alg = ui->el_alg->currentIndex();
    int col = ui->el_col->currentIndex();
    int bgc_col = ui->el_bgc->isChecked();
    c = new QColor;
    set_colour(bgc_col, col, c);
    if (alg == 0)
        draw_el_kanon(x, y, a, b, c, scene);
    if (alg == 1)
        draw_el_param(x, y, a, b, c, scene);
    /*
    if (alg == 2)
        draw_bres(x, y, r, c, scene);
    if (alg == 3)
        draw_mid(x, y, r, c, scene);
        */
    if (alg == 4)
        draw_el_library(x, y, a, b, c, scene);
}
