#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QGraphicsScene>
#include <qmath.h>
#define a 20
#define b 20
#define r 2
#define c 2
#define d 2

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
    blackpen.setWidth(3);
    blueBrush.setWidth(3);

    float y = 0;

    for (float x = 0; x < 50; x += 0.1)
    {
        y = sqrt(2500 - qPow(x, 2));
        scene->addEllipse(x, -y, 5, 5, blackpen);
        scene->addEllipse(x, y, 5, 5, blackpen);
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
