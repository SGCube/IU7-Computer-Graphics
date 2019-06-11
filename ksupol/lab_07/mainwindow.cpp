#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "check.h"
#include <stdio.h>
#include <QMessageBox>
#include <QDebug>
#include <math.h>
#include <stdlib.h>

#define EPS 0.0001

#define OK 0
#define ENDD -1
#define DRAW 1

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
    paint->set_pen();
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
        clip_line(i);
}

void MainWindow::clip_line(int i)
{
    unsigned char t1 = 0;
    unsigned char t2 = 0;
    QLine line = lines->value(i);
    QPoint p1 = line.p1();
    QPoint p2 = line.p2();
    QPoint res1, res2, p;
    pointCode(p1, &t1);
    pointCode(p2, &t2);

    int left = clipper->value(0), right = clipper->value(1),
            bottom = clipper->value(2), top = clipper->value(3);
    float m = pow(10, 10);
    int x, y;
    int vis = check_visibility(t1, t2);
    if (vis == 1)
    {
        put_line(p1, p2);
        return;
    }
    if (vis == -1)
        return;
    if (p1.x() != p2.x())
        m = float(p2.y() - p1.y()) / (p2.x() - p1.x());
    else
        m = 0;
    if (t1 == 0)
    {
        res1 = p1;
        p = p2;
        checkPointPosition(res1, res2, m, p);
        return;
    }
    if (t2 == 0)
    {
        res1 = p2;
        p = p1;
        checkPointPosition(res1, res2, m, p);
        return;
    }
    if (m == 0 && p1.x() >= left && p1.x() <= right)
    {
        res1.setX(p1.x());
        res1.setY(bottom);
        res2.setX(p1.x());
        res2.setY(top);
        put_line(res1, res2);
        return;
    }
    y = int(m * (left - p1.x()) + p1.y());
    if (y >= bottom && y <= top)
    {
        res1.setX(left);
        res1.setY(y);
        bool fl = find_bottom_crossing(res1, res2, p2, m);
        if (!fl)
            fl = find_right_crossing(res1, res2, p2, m);
        if (!fl)
            fl = find_top_crossing(res1, res2, p2, m);
        return;
    }
    y = int(m * (right - p1.x()) + p1.y());
    if (y >= bottom && y <= top)
    {
        res1.setX(right);
        res1.setY(y);
        bool fl = find_bottom_crossing(res1, res2, p2, m);
        if (!fl)
            fl = find_left_crossing(res1, res2, p2, m);
        if (!fl)
            fl = find_top_crossing(res1, res2, p2, m);
        return;
    }
    x = int((bottom - p1.y())/m + p1.x());
    if (x >= left && x <= right)
    {
        res1.setX(x);
        res1.setY(bottom);
        bool fl = find_right_crossing(res1, res2, p2, m);
        if (!fl)
            fl = find_left_crossing(res1, res2, p2, m);
        if (!fl)
            fl = find_top_crossing(res1, res2, p2, m);
        return;
    }
    x = int((top - p1.y())/m + p1.x());
    if (x >= left && x <= right)
    {
        res1.setX(x);
        res1.setY(top);
        bool fl = find_right_crossing(res1, res2, p2, m);
        if (!fl)
            fl = find_left_crossing(res1, res2, p2, m);
        if (!fl)
            fl = find_bottom_crossing(res1, res2, p2, m);
        return;
    }
}

bool MainWindow::find_bottom_crossing(QPoint res1, QPoint res2, QPoint p2, float m)
{
    int left = clipper->value(0), right = clipper->value(1),
            bottom = clipper->value(2), top = clipper->value(3);
    int x = int((bottom - p2.y())/m + p2.x());
    if (x >= left && x <= right)
    {
        res2.setX(x);
        res2.setY(bottom);
        put_line(res1, res2);
        return true;
    }
    return false;
}

bool MainWindow::find_top_crossing(QPoint res1, QPoint res2, QPoint p2, float m)
{
    int left = clipper->value(0), right = clipper->value(1),
            bottom = clipper->value(2), top = clipper->value(3);
    int x = int((top - p2.y())/m + p2.x());
    if (x >= left && x <= right)
    {
        res2.setX(x);
        res2.setY(top);
        put_line(res1, res2);
    }
}

bool MainWindow::find_right_crossing(QPoint res1, QPoint res2, QPoint p2, float m)
{
    int left = clipper->value(0), right = clipper->value(1),
            bottom = clipper->value(2), top = clipper->value(3);
    int y = int(m * (right - p2.x()) + p2.y());
    if (y >= bottom && y <= top)
    {
        res2.setX(right);
        res2.setY(y);
        put_line(res1, res2);
    }
}

bool MainWindow::find_left_crossing(QPoint res1, QPoint res2, QPoint p2, float m)
{
    int left = clipper->value(0), right = clipper->value(1),
            bottom = clipper->value(2), top = clipper->value(3);
    int y = int(m * (left - p2.x()) + p2.y());
    if (y >= bottom && y <= top)
    {
        res2.setX(left);
        res2.setY(y);
        put_line(res1, res2);
    }
}

void MainWindow::checkPointPosition(QPoint res1, QPoint res2, float m, QPoint p)
{
    int left = clipper->value(0), right = clipper->value(1),
            bottom = clipper->value(2), top = clipper->value(3);
    int x, y;
    if (p.x() < left)
    {
        y = int(m * (left - p.x()) + p.y());
        if (y >= bottom && y <= top)
        {
            res2.setX(left);
            res2.setY(y);
            put_line(res1, res2);
            return;
        }
        if (p.y() < bottom)
        {
            x = int((bottom - p.y())/m + p.x());
            if (x >= left && x <= right)
            {
                res2.setX(x);
                res2.setY(bottom);
                put_line(res1, res2);
                return;
            }
        }
        if (p.y() > top)
        {
            x = int((top - p.y())/m + p.x());
            if (x >= left && x <= right)
            {
                res2.setX(x);
                res2.setY(top);
                put_line(res1, res2);
                return;
            }
        }
    }
    if (p.x() > right)
    {
        y = int(m * (right - p.x()) + p.y());
        if (y >= bottom && y <= top)
        {
            res2.setX(right);
            res2.setY(y);
            put_line(res1, res2);
            return;
        }
        if (p.y() < bottom)
        {
            x = int((bottom - p.y())/m + p.x());
            if (x >= left && x <= right)
            {
                res2.setX(x);
                res2.setY(bottom);
                put_line(res1, res2);
                return;
            }
        }
        if (p.y() > top)
        {
            x = int((top - p.y())/m + p.x());
            if (x >= left && x <= right)
            {
                res2.setX(x);
                res2.setY(top);
                put_line(res1, res2);
                return;
            }
        }
    }
    if (p.x() >= left && p.x() <= right)
    {
        if (m == 0)
        {
            if (p.y() > top)
            {
                res2.setX(p.x());
                res2.setY(top);
                put_line(res1, res2);
                return;
            }
            else
            {
                res2.setX(p.x());
                res2.setY(bottom);
                put_line(res1, res2);
                return;
            }
        }
        else
        {
            if (p.y() > top)
            {
                x = int((top - p.y())/m + p.x());
                res2.setX(x);
                res2.setY(top);
                put_line(res1, res2);
                return;
            }
            else
            {
                x = int((bottom - p.y())/m + p.x());
                res2.setX(x);
                res2.setY(bottom);
                put_line(res1, res2);
                return;
            }
        }
    }
}

void MainWindow::put_line(QPoint r1, QPoint r2)
{
    paint->begin(img);
    paint->set_double_pen();
    paint->put_line(r1.x(), r1.y(), r2.x(), r2.y());
    QGraphicsScene *scene = ui->graphics->scene();
    scene->addPixmap(QPixmap::fromImage(*img));
    paint->end();
}

void MainWindow::pointCode(QPoint a, unsigned char *t)
{
    if (a.x() < clipper->value(0))
        *t = *t | LEFT;
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
