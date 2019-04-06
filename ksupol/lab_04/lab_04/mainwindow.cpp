#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "check.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_build_cir_clicked()
{
    double x;
    double y;
    QString cor_x = ui->cor_x->text();
    QString cor_y = ui->cor_y->text();
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
        int check = check_point(cor_x);
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
    QString rad = ui->rad->text();
    if (rad == NULL)
    {
        QMessageBox::critical(this, "Ошибка", "Введите радиус окружности!");
        return;
    }
    double r = rad.toFloat();
}
