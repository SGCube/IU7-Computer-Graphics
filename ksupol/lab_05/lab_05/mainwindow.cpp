#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "check.h"
#include "paint.h"
#include <QGraphicsScene>
#include <QColorDialog>
#include <QColor>
#include <QDebug>
#include <QMessageBox>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    const QStringList a = {"X", "Y"};
    this->setWindowTitle("Лабораторная работа №1");

    scene = new QGraphicsScene(this);
    ui->graphics->setScene(scene);

    ui->table->setColumnCount(2); // Указываем число колонок
    ui->table->setShowGrid(true); // Включаем сетку
    // Устанавливаем заголовки колонок
    ui->table->setHorizontalHeaderLabels(a);
    ui->table->horizontalHeader()->resizeSection(0, 80);
    ui->table->horizontalHeader()->resizeSection(1, 80);
    ui->table->setEditTriggers(QAbstractItemView :: NoEditTriggers);
    ui->table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphics->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphics->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphics->setMouseTracking(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_add_poin_clicked()
{
    QString line_x = ui->cor_x->text();
    QString line_y = ui->cor_y->text();
    if (line_x == NULL || line_y == NULL)
    {
        QMessageBox::critical(this, "Ошибка", "Введите координаты!");
        return;
    }
    int check = check_point(line_x);
    if (check != 0)
    {
        QMessageBox::critical(this, "Ошибка", "Введите корректную координату X!");
        return;
    }
    check = check_point(line_y);
    if (check != 0)
    {
        QMessageBox::critical(this, "Ошибка", "Введите корректную координату Y!");
        return;
    }
    insert_into_table(line_x, line_y);
    int x = line_x.toInt();
    int y = line_y.toInt();
    points[amount].x = x;
    points[amount].y = y;
    amount++;
    int b = ui->col_b->currentIndex();
    set_color(c, b);
    if (amount > 1)
        paint(amount, points, scene, c);
}

void MainWindow::insert_into_table(QString x, QString y)
{
    ui->table->insertRow(amount);
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setText(x);
    ui->table->setItem(amount,0,item);
    QTableWidgetItem *item2 = new QTableWidgetItem();
    item2->setText(y);
    ui->table->setItem(amount,1,item2);
}

void MainWindow::on_lock_clicked()
{
    points[amount].x = points[0].x;
    points[amount].y = points[0].y;
    QString x = QString::number(points[0].x);
    QString y = QString::number(points[0].y);
    insert_into_table(x, y);
    amount++;
}

void MainWindow::on_clear_clicked()
{
    scene->clear();
    while (amount >= 0)
    {
        ui->table->removeRow(amount);
        amount--;
    }
    clear_array();
    amount = 0;
}

void MainWindow::on_clear_table_clicked()
{
    scene->clear();
    while (amount >= 0)
    {
        ui->table->removeRow(amount);
        amount--;
    }
    clear_array();
    amount = 0;
}

void MainWindow::clear_array()
{
    for (int i = 0; i < amount; i++)
    {
        points[i].x = 0;
        points[i].y = 0;
    }
}
