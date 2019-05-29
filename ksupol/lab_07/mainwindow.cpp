#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "check.h"
#include <stdio.h>
#include <QMessageBox>
#include <QDebug>
#include <qmath.h>

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

void MainWindow::on_pushButton_clicked()
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
    line_or_clipper = false;
}

void MainWindow::on_line_clicked()
{
    line_or_clipper = true;
}

void MainWindow::on_setClipper_clicked()
{
    if (!line_or_clipper)
    {
        w = ui->width->text().toInt();
        h = ui->height->text().toInt();
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    img->fill(Qt::white);
    QGraphicsScene *scene = ui->graphics->scene();
    scene->clear();
    scene->addPixmap(QPixmap::fromImage(*img));
    for (int i = 0; i < lines->size(); i++)
    {
        QLine line = lines->value(i);
        QPoint r1, r2, q;
        char t1 = 0, t2 = 0;
        lineCodes(line, &t1, &t2);
        bool pr = true;
        float m = qPow(10, 30);
        if ((t1 == 0) && (t2 == 0))
        {
            r1 = line.p1();
            r2 = line.p2();
            put_line(r1, r2);
        }
        else
        {
            char pl = t1 & t2;
            pr = false;
            if (t1 == 0)
            {
                r1 = line.p1();
                q = line.p2();
                int j = 2;
                if (line.x1 == line.x2)
                {
                    if ()
                }
            }

        }
    }
}

void MainWindow::put_line(QPoint r1, QPoint r2)
{
    paint->begin(img);
    paint->set_pen();
    paint->put_line(r1.x(), r1.y(), r2.x(), r2.y());
    QGraphicsScene *scene = ui->graphics->scene();
    scene->addPixmap(QPixmap::fromImage(*img));
    paint->end();
}

void MainWindow::lineCodes(QLine line, char *t1, char *t2)
{
    if (line.x1() < clipper->value(0))
        *t1 |= 1;
    if (line.x1() > clipper->value(1))
        *t1 |= 2;
    if (line.y1() > clipper->value(2))
        *t1 |= 4;
    if (line.y1() < clipper->value(3))
        *t1 |= 8;

    if (line.x2() < clipper->value(0))
        *t2 |= 1;
    if (line.x2() > clipper->value(1))
        *t2 |= 2;
    if (line.y2() > clipper->value(2))
        *t2 |= 4;
    if (line.y2() < clipper->value(3))
        *t2 |= 8;
}
