#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "check.h"
#include <stdio.h>
#include <QMessageBox>
#include <QDebug>
#include <math.h>
#include <stdlib.h>

MainWindow::MainWindow(QImage *image, QVector<QLine> *segments, QVector<int> *cutter,
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
    ui->table->setColumnCount(2);
    ui->table->setShowGrid(true);
    ui->table->setHorizontalHeaderLabels(a);
    ui->table->horizontalHeader()->resizeSection(0, 90);
    ui->table->horizontalHeader()->resizeSection(1, 90);
    ui->table->setEditTriggers(QAbstractItemView :: NoEditTriggers);
    ui->table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    text = ui->text;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::add_scene(QGraphicsScene *scene)
{
    ui->graphics->setScene(scene);
}

void MainWindow::insert_into_table(QString x, QString y)
{
    int row = ui->table->rowCount();
    ui->table->insertRow(row);
    int row1 = ui->table->rowCount() - 1;
    QTableWidgetItem *xx = new QTableWidgetItem();
    ui->table->setItem(row1, 0, xx);
    xx->setText(x);
    QTableWidgetItem *yy = new QTableWidgetItem();
    ui->table->setItem(row1, 1, yy);
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
    insert_into_table(sx, sy);
    insert_into_table(ex, ey);
    insert_into_table("X", "Y");
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
    int row = ui->table->rowCount();
    do
    {
        ui->table->removeRow(row - 1);
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
    line = false;
}

void MainWindow::on_line_clicked()
{
    line = true;
}

void MainWindow::on_clip_clicked()
{
    if (lines->size() == 0)
    {
        QMessageBox::critical(this, "Ошибка", "Введите отрезки!");
        return;
    }
    if (clipper->size() == 0)
    {
        QMessageBox::critical(this, "Ошибка", "Введите отсекатель!");
        return;
    }
    for (int i = 0; i < lines->size(); i++)
        clip_line();
}

void MainWindow::clip_line()
{
    unsigned char t1 = 0;
    unsigned char t2 = 0;
    QLine line = lines->value(i);
    QPoint p1 = line.p1();
    QPoint p2 = line.p2();
}

/*
void MainWindow::on_clip_clicked()
{
    if (lines->size() == 0)
    {
        QMessageBox::critical(this, "Ошибка", "Введите отрезки!");
        return;
    }
    if (clipper->size() == 0)
    {
        QMessageBox::critical(this, "Ошибка", "Введите отсекатель!");
        return;
    }
    //paint->set_pen();
    for (int i = 0; i < lines->size(); i++)
    {
        unsigned char t1 = 0;
        unsigned char t2 = 0;
        QLine line = lines->value(i);
        QPoint p1 = line.p1();
        QPoint p2 = line.p2();
        lineCodes(line, &t1, &t2);
        qDebug() << t1 << t2;
        int pr;

        int fl = 0;
        float m = 1;
        if (p2.x() == p1.x())
            fl = -1;
        else
        {
            m = float(p2.y() - p1.y())/(p2.x() - p1.x());
            if (m == 0)
                fl = 1;
        }
        unsigned char ms[] = {LEFT, RIGHT, BOTTOM, TOP};
        for (int j = 0; j < 4; j++)
        {
            pr = check_visibility(t1, t2);
            //qDebug() << pr;
            if (pr == -1)
                break;
            else if (pr == 1)
                break;
            unsigned char c1 = t1 & ms[i];
            unsigned char c2 = t2 & ms[i];
            if (c1 == c2)
                continue;
            if (c1 == 0)
            {
                QPoint t = p1;
                p1 = p2;
                p2 = t;
            }
            if (fl != -1 && j < 2)
            {
                    int tmp_y = round(m * (clipper->value(j) - p1.x()) + p1.y());
                    p1.setY(tmp_y);

                    int tmp_x = clipper->value(j);
                    p1.setX(tmp_x);
            }
            else
            {
                if (fl != -1)
                {
                    int tmp_x = round((1/m) * (clipper->value(j) - p1.y())) + p1.x();
                    p1.setX(tmp_x);
                }
                int tmp_y = clipper->value(j);
                p1.setY(tmp_y);
            }
        }
        if (pr != -1)
            put_line(p1, p2);
    }
}
*/

void MainWindow::put_line(QPoint r1, QPoint r2)
{
    paint->begin(img);
    paint->set_double_pen();
    paint->put_line(r1.x(), r1.y(), r2.x(), r2.y());
    QGraphicsScene *scene = ui->graphics->scene();
    scene->addPixmap(QPixmap::fromImage(*img));
    paint->end();
}

void MainWindow::lineCode(QPoint a, unsigned char *t1)
{
    if (a.x() < clipper->value(0))
        *t = *t1 | LEFT;
    if (a.x() > clipper->value(1))
        *t = *t | RIGHT;
    if (a.y() < clipper->value(2))
        *t = *t | BOTTOM;
    if (a.y() > clipper->value(3))
        *t = *t |TOP;
}

int MainWindow::check_visibility(unsigned char t1,
                                 unsigned char t2)
{
    if (t1 == 0 && t2 == 0)
        return 1;
    unsigned char p = t1 & t2;
    if (p != 0)
        return -1;
    return 0;
}

void MainWindow::on_resultColor_currentIndexChanged(int index)
{
    paint->color(index);
}
