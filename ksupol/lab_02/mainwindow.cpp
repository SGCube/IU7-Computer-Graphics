#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QGraphicsScene>
#define a 2
#define b 2
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

    scene->addEllipse(0, 0, 25, 25, blueBrush);

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
