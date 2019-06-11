#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "check.h"
#include "calc.h"
#include <stdio.h>
#include <QMessageBox>
#include <QDebug>
#include <qmath.h>

#define WORK 0
#define EXIT -1

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
    this->setWindowTitle("Лабораторная работа №8");

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

    row = ui->table_clipper->rowCount();
    do
    {
        ui->table_clipper->removeRow(row - 1);
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

void MainWindow::on_clip_clicked()
{
    if (lines->size() == 0)
    {
        QMessageBox::critical(this, "Ошибка", "Введите отрезок/отрезки!");
        return;
    }
    if (clipper->size() == 0)
    {
        QMessageBox::critical(this, "Ошибка", "Введите отсекатель!");
        return;
    }
    cutter = from_points_to_lines();
    bool convex = is_convex();
    if (!convex)
    {
        QMessageBox::critical(this, "Ошибка", "Отсекатель не выпуклый!");
        return;
    }
    calculate_normals();
    for (int i = 0; i < lines->size(); i++)
        cut_line(i);
    draw_result();
}

void MainWindow::cut_line(int i)
{
    QLine line = lines->value(i);
    qDebug() << line;
    int rc = WORK;
    double t_bottom = 0;
    double t_top = 1;
    double t_cur;
    QLine cur_edge;
    vector D = vector(line);
    vector W;
    int D_scalar, W_scalar;
    for (int i = 0; i < cutter.size() && rc == WORK; i++)
    {
        cur_edge = cutter.value(i);
        W = vector(line.p1(), cur_edge.p1());
        D_scalar = scalar_mult(normals[i], D);
        W_scalar = scalar_mult(W, normals[i]);
        if (D_scalar == 0)
        {
            if (W_scalar < 0)
                rc = EXIT;
        }
        else
        {
            t_cur = -W_scalar / (double)D_scalar;
            if (D_scalar > 0)
            {
                if (t_cur > 1)
                    rc = EXIT;
                else
                {
                    if (t_bottom > t_cur)
                        t_bottom = t_bottom;
                    else
                        t_bottom = t_cur;
                }
            }
            else
            {
                if (t_cur < 0)
                    rc = EXIT;
                else
                {
                    if (t_top < t_cur)
                        t_top = t_top;
                    else
                        t_top = t_cur;
                }
            }
        }
    }
    if (rc != EXIT)
    {
        if (t_bottom <= t_top)
        {
            QPoint p1 = calculate_P(line.p1(), line.p2(), t_bottom);
            QPoint p2 = calculate_P(line.p1(), line.p2(), t_top);
            QLine res = QLine(p1, p2);
            result.push_back(res);
        }
    }
}

void MainWindow::draw_result()
{
    for (int i = 0; i < result.size(); i++)
    {
        QLine line = result.value(i);
        paint->begin(img);
        paint->set_double_pen();
        paint->put_line(line.x1(), line.y1(), line.x2(), line.y2());
        QGraphicsScene *scene = ui->graphics->scene();
        scene->addPixmap(QPixmap::fromImage(*img));
        paint->end();
    }
}

QVector<QLine> MainWindow::from_points_to_lines()
{
    QVector<QLine> a;
    int size = clipper->size();
    for (int i = 0; i < size - 1; i++)
    {
        a.push_back(QLine(clipper->value(i).x(), clipper->value(i).y(),
                    clipper->value(i+1).x(), clipper->value(i+1).y()));
    }
    a.push_back(QLine(clipper->value(size-1).x(), clipper->value(size-1).y(),
                clipper->value(0).x(), clipper->value(0).y()));
    return a;
}

bool MainWindow::is_convex()
{
    vector a = vector(cutter.value(0));
    vector b, res;
    int sign = 0;
    for (int i = 1; i < cutter.size() - 1; i++)
    {
        b = vector(cutter.value(i));
        multiply_vectors(a, b, res);
        if (sign == 0)
            sign = sign_func(res.z);
        if (res.z && sign != sign_func(res.z))
        {
            direction = 0;
            return false;
        }
        a = b;
    }
    direction = sign;
    return true;
}

void MainWindow::calculate_normals()
{
    vector tmp;
    for (int i = 0; i < cutter.size(); i++)
    {
        tmp = vector(cutter.value(i));
        if (direction == 1)
            normals.push_back(vector(-tmp.y, tmp.x));
        else
            normals.push_back(vector(tmp.y, -tmp.x));
    }
}

void MainWindow::on_resultColor_currentIndexChanged(int index)
{
    paint->color(index);
}
