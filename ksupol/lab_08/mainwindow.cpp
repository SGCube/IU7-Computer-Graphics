#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "check.h"
#include <stdio.h>
#include <QMessageBox>
#include <QDebug>
#include <qmath.h>

MainWindow::MainWindow(QImage *image, QVector<QLine> *segments, QVector<QPoint> *cutter,
                       Paint *p, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    paint(p),
    img(image),
    lines(segments),
    clipper(cutter)
{
    ui->setupUi(this);
    this->setWindowTitle("Лабораторная работа №7");

    ui->graphics->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphics->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphics->setMouseTracking(true);

    const QStringList a = {"X", "Y"};
    ui->table_lines->setColumnCount(2);
    ui->table_lines->setShowGrid(true);
    ui->table_lines->setHorizontalHeaderLabels(a);
    ui->table_lines->horizontalHeader()->resizeSection(0, 90);
    ui->table_lines->horizontalHeader()->resizeSection(1, 90);
    ui->table_lines->setEditTriggers(QAbstractItemView :: NoEditTriggers);
    ui->table_lines->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->table_clipper->setColumnCount(2);
    ui->table_clipper->setShowGrid(true);
    ui->table_clipper->setHorizontalHeaderLabels(a);
    ui->table_clipper->horizontalHeader()->resizeSection(0, 90);
    ui->table_clipper->horizontalHeader()->resizeSection(1, 90);
    ui->table_clipper->setEditTriggers(QAbstractItemView :: NoEditTriggers);
    ui->table_clipper->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::add_scene(QGraphicsScene *scene)
{
    ui->graphics->setScene(scene);
}

void MainWindow::insert_into_table_lines(QString x, QString y)
{
    int row = ui->table_lines->rowCount();
    ui->table_lines->insertRow(row);
    int row1 = ui->table_lines->rowCount() - 1;
    QTableWidgetItem *xx = new QTableWidgetItem();
    ui->table_lines->setItem(row1, 0, xx);
    xx->setText(x);
    QTableWidgetItem *yy = new QTableWidgetItem();
    ui->table_lines->setItem(row1, 1, yy);
    yy->setText(y);
}

void MainWindow::insert_into_table_clipper(QString x, QString y)
{
    int row = ui->table_clipper->rowCount();
    ui->table_clipper->insertRow(row);
    int row1 = ui->table_clipper->rowCount() - 1;
    QTableWidgetItem *xx = new QTableWidgetItem();
    ui->table_clipper->setItem(row1, 0, xx);
    xx->setText(x);
    QTableWidgetItem *yy = new QTableWidgetItem();
    ui->table_clipper->setItem(row1, 1, yy);
    yy->setText(y);
}

void MainWindow::on_inputLine_clicked()
{
    QString sx = ui->sx->text();
    QString sy = ui->sy->text();
    if (sx == NULL || sy == NULL)
    {
        QMessageBox::critical(this, "Ошибка", "Введите начало отрезка!");
        return;
    }
    int check = checkPoint(sx);
    if (check != 0)
    {
        QMessageBox::critical(this, "Ошибка", "Введите корректную координату X начала отрезка!");
        return;
    }
    check = checkPoint(sy);
    if (check != 0)
    {
        QMessageBox::critical(this, "Ошибка", "Введите корректную координату Y начала отрезка!");
        return;
    }
    QString ex = ui->ex->text();
    QString ey = ui->ey->text();
    if (ex == NULL || ey == NULL)
    {
        QMessageBox::critical(this, "Ошибка", "Введите конец отрезка!");
        return;
    }
    check = checkPoint(ex);
    if (check != 0)
    {
        QMessageBox::critical(this, "Ошибка", "Введите корректную координату X конца отрезка!");
        return;
    }
    check = checkPoint(ey);
    if (check != 0)
    {
        QMessageBox::critical(this, "Ошибка", "Введите корректную координату Y конца отрезка!");
        return;
    }
    insert_into_table_lines(sx, sy);
    insert_into_table_lines(ex, ey);
    insert_into_table_lines("X", "Y");
    int Sx = sx.toInt();
    int Sy = sy.toInt();
    int Ex = ex.toInt();
    int Ey = ey.toInt();
    lines->push_back(QLine(QPoint(Sx, Sy), QPoint(Ex, Ey)));

    paint->begin(img);
    paint->set_pen();
    paint->put_line(Sx, Sy, Ex, Ey);
    QGraphicsScene *scene = ui->graphics->scene();
    scene->addPixmap(QPixmap::fromImage(*img));
    paint->end();
}

void MainWindow::on_clear_clicked()
{
    int row = ui->table_lines->rowCount();
    do
    {
        ui->table_lines->removeRow(row - 1);
        row--;
    }
    while (row > 0);
    img->fill(Qt::white);
    QGraphicsScene *scene = ui->graphics->scene();
    scene->clear();
    scene->addPixmap(QPixmap::fromImage(*img));
    lines->clear();
    clipper->clear();
    set_clipper = false;
}

void MainWindow::on_lineColor_currentIndexChanged(int index)
{
    paint->color(index);
}

void MainWindow::on_clipperColor_currentIndexChanged(int index)
{
    paint->colorClipper(index);
}

void MainWindow::on_clipper_clicked()
{
    line_or_clipper = false;
}

void MainWindow::on_line_clicked()
{
    line_or_clipper = true;
}

void MainWindow::on_inputClipper_clicked()
{
    QString clipX = ui->clipX->text();
    QString clipY = ui->clipY->text();

    if (clipX == NULL || clipY == NULL)
    {
        QMessageBox::critical(this, "Ошибка", "Введите координаты точки!");
        return;
    }
    int check = checkPoint(clipX);
    if (check != 0)
    {
        QMessageBox::critical(this, "Ошибка", "Введите корректную координату X!");
        return;
    }
    check = checkPoint(clipY);
    if (check != 0)
    {
        QMessageBox::critical(this, "Ошибка", "Введите корректную координату Y!");
        return;
    }
    insert_into_table_clipper(clipX, clipY);
    int x = clipX.toInt();
    int y = clipY.toInt();
    QPoint a;
    a.setX(x);
    a.setY(y);
    clipper->push_back(a);
    paint->begin(img);
    paint->set_pen();
    if (clipper->size() > 1)
    {
        QPoint last = clipper->back();
        paint->put_line(x, y, last.x(), last.y());
    }
    QGraphicsScene *scene = ui->graphics->scene();
    scene->addPixmap(QPixmap::fromImage(*img));
    paint->end();
}
