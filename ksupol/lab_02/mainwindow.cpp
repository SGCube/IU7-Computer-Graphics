#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QGraphicsScene>
#include <qmath.h>
#define a 20
#define b 20
#define r 30
#define c 10
#define d 20

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Лабораторная работа №2");

    scene = new QGraphicsScene(this);
    ui->graphics->setScene(scene);

    QPen blueBrush(Qt::blue);
    QPen blackpen(Qt::black);
    blackpen.setWidth(1);
    blueBrush.setWidth(1);

    float y = 0;

    for (float x = -r; x < r; x += 0.05)
    {
        y = sqrt(qPow(r, 2) - qPow(x, 2));
        scene->addEllipse(x, -y, 3, 3, blackpen);
        scene->addEllipse(x, y, 3, 3, blackpen);
    }
    for (float x = - c; x < 100; x += 0.1)
    {
        y = sqrt(x + c);
        scene->addEllipse(x, -3*y, 3, 3, blackpen);
        scene->addEllipse(x, 3*y, 3, 3, blackpen);
    }
    for (float x = - c; x < r; x += 0.1)
    {
        y = sqrt(x + c);
        for (float ac = 0; ac < y; ac += 0.1)
        {
            if (qPow(x, 2) + qPow(ac, 2) < qPow(r, 2))
            {
                scene->addEllipse(x, -3*ac, 3, 3, blackpen);
                scene->addEllipse(x, 3*ac, 3, 3, blackpen);
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_rotate_clicked()
{
    if (ui->lineEdit_rotate->text() == NULL)
    {
        QMessageBox::warning(this, "Ошибка", "Заполните необходимые поля!");
        return;
    }

}
