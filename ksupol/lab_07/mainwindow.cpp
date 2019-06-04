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


/*
void MainWindow::on_clip_clicked()
{
    img->fill(Qt::white);
    QGraphicsScene *scene = ui->graphics->scene();
    scene->clear();
    scene->addPixmap(QPixmap::fromImage(*img));
    for (int i = 0; i < lines->size(); i++)
    {
        QLine line = lines->value(i);
        QPoint r1, r2, q;
        QPoint cr;
        int j = 0;
        unsigned char t1 = 0x0, t2 = 0x0;
        int s1 = 0, s2 = 0;
        lineCodes(line, &t1, &t2, &s1, &s2);
        bool pr = true;
        float m = pow(10, 30);
        if ((s1 == 0) && (s2 == 0))
        {
            r1 = line.p1();
            r2 = line.p2();
            put_line(r1, r2, pr);
            continue;
        }
        char pl = t1 & t2;
        if (pl != 0)
            continue;
        if (s1 == 0)
        {
            r1 = line.p1();
            q = line.p2();
            j = 2;
            if (line.x1() == line.x2())
            {
                if (m != 0)
                {
                    if (q.y() < clipper->value(3))
                    {
                        float x = (clipper->value(3) - q.y()) / m + q.x();
                        if (clipper->value(0) <= x && x <= clipper->value(1))
                        {
                            if (j == 1)
                            {
                                r1 = QPoint(round(x), clipper->value(3));
                                a(&j, r1, r2, clipper, pr, q, line, m);
                            }
                            else
                            {
                                r2 = QPoint(round(x), clipper->value(3));
                                a(&j, r1, r2, clipper, pr, q, line, m);
                            }
                        }
                        if (q.y() > clipper->value(2))
                        {
                            x = (clipper->value(2) - q.y())/m + q.x();
                            if (clipper->value(0) <= x && x <= clipper->value(1))
                            {
                                if (j == 1)
                                {
                                    r1 = QPoint(round(x), clipper->value(2));
                                    a(&j, r1, r2, clipper, pr, q, line, m);
                                }
                                else
                                {
                                    r2 = QPoint(round(x), clipper->value(2));
                                    a(&j, r1, r2, clipper, pr, q, line, m);
                                }
                            }
                            return;
                        }
                    }
                    if (q.y() > clipper->value(2))
                    {
                        float x = (clipper->value(2) - q.y())/m + q.x();
                        if (clipper->value(0) <= x && x <= clipper->value(1))
                        {
                            if (j == 1)
                            {
                                r1 = QPoint(round(x), clipper->value(2));
                                a(&j, r1, r2, clipper, pr, q, line, m);
                            }
                            else
                            {
                                r2 = QPoint(round(x), clipper->value(2));
                                a(&j, r1, r2, clipper, pr, q, line, m);
                            }
                        }
                        return;
                    }
                }
                return;
            }
            m = (line.y2() - line.y1())/(line.x2() - line.x1());
            if (q.x() < clipper->value(0))
            {
                float y = m * (clipper->value(0) - q.x()) + q.y();
                if (clipper->value(3) <= y && y <= clipper->value(2))
                {
                    if (j == 1)
                    {
                        r1 = QPoint(clipper->value(0), round(y));
                        a(&j, r1, r2, clipper, pr, q, line, m);
                    }
                    else
                    {
                        r2 = QPoint(clipper->value(0), round(y));
                        a(&j, r1, r2, clipper, pr, q, line, m);
                    }
                }
                if (q.x() > clipper->value(1))
                {
                    float y = m * (clipper->value(1) - q.x()) + q.y();
                    if (clipper->value(3) <= y && y <= clipper->value(2))
                    {
                        if (j == 1)
                        {
                            r1 = QPoint(clipper->value(1), round(y));
                            a(&j, r1, r2, clipper, pr, q, line, m);
                        }
                        else
                        {
                            r2 = QPoint(clipper->value(1), round(y));
                            a(&j, r1, r2, clipper, pr, q, line, m);
                        }
                    }
                }
                if (m != 0)
                {
                    if (q.y() < clipper->value(3))
                    {
                        float x = (clipper->value(3) - q.y()) / m + q.x();
                        if (clipper->value(0) <= x && x <= clipper->value(1))
                        {
                            if (j == 1)
                            {
                                r1 = QPoint(round(x), clipper->value(3));
                                a(&j, r1, r2, clipper, pr, q, line, m);
                            }
                            else
                            {
                                r2 = QPoint(round(x), clipper->value(3));
                                a(&j, r1, r2, clipper, pr, q, line, m);
                            }
                        }
                        if (q.y() > clipper->value(2))
                        {
                            x = (clipper->value(2) - q.y())/m + q.x();
                            if (clipper->value(0) <= x && x <= clipper->value(1))
                            {
                                if (j == 1)
                                {
                                    r1 = QPoint(round(x), clipper->value(2));
                                    a(&j, r1, r2, clipper, pr, q, line, m);
                                }
                                else
                                {
                                    r2 = QPoint(round(x), clipper->value(2));
                                    a(&j, r1, r2, clipper, pr, q, line, m);
                                }
                            }
                            return;
                        }
                    }
                    if (q.y() > clipper->value(2))
                    {
                        float x = (clipper->value(2) - q.y())/m + q.x();
                        if (clipper->value(0) <= x && x <= clipper->value(1))
                        {
                            if (j == 1)
                            {
                                r1 = QPoint(round(x), clipper->value(2));
                                a(&j, r1, r2, clipper, pr, q, line, m);
                            }
                            else
                            {
                                r2 = QPoint(round(x), clipper->value(2));
                                a(&j, r1, r2, clipper, pr, q, line, m);
                            }
                        }
                        return;
                    }
                }
                return;
            }
            if (q.x() > clipper->value(1))
            {
                float y = m * (clipper->value(1) - q.x()) + q.y();
                if (clipper->value(3) <= y && y <= clipper->value(2))
                {
                    if (j == 1)
                    {
                        r1 = QPoint(clipper->value(1), round(y));
                        a(&j, r1, r2, clipper, pr, q, line, m);
                    }
                    else
                    {
                        r2 = QPoint(clipper->value(1), round(y));
                        a(&j, r1, r2, clipper, pr, q, line, m);
                    }
                }
            }
            if (m != 0)
            {
                if (q.y() < clipper->value(3))
                {
                    float x = (clipper->value(3) - q.y()) / m + q.x();
                    if (clipper->value(0) <= x && x <= clipper->value(1))
                    {
                        if (j == 1)
                        {
                            r1 = QPoint(round(x), clipper->value(3));
                            a(&j, r1, r2, clipper, pr, q, line, m);
                        }
                        else
                        {
                            r2 = QPoint(round(x), clipper->value(3));
                            a(&j, r1, r2, clipper, pr, q, line, m);
                        }
                    }
                    if (q.y() > clipper->value(2))
                    {
                        x = (clipper->value(2) - q.y())/m + q.x();
                        if (clipper->value(0) <= x && x <= clipper->value(1))
                        {
                            if (j == 1)
                            {
                                r1 = QPoint(round(x), clipper->value(2));
                                a(&j, r1, r2, clipper, pr, q, line, m);
                            }
                            else
                            {
                                r2 = QPoint(round(x), clipper->value(2));
                                a(&j, r1, r2, clipper, pr, q, line, m);
                            }
                        }
                        return;
                    }
                }
                if (q.y() > clipper->value(2))
                {
                    float x = (clipper->value(2) - q.y())/m + q.x();
                    if (clipper->value(0) <= x && x <= clipper->value(1))
                    {
                        if (j == 1)
                        {
                            r1 = QPoint(round(x), clipper->value(2));
                            a(&j, r1, r2, clipper, pr, q, line, m);
                        }
                        else
                        {
                            r2 = QPoint(round(x), clipper->value(2));
                            a(&j, r1, r2, clipper, pr, q, line, m);
                        }
                    }
                    return;
                }
            }
        }
        if (s2 == 0)
        {
            r1 = line.p2();
            q = line.p1();
            j = 2;
            if (line.x1() == line.x2())
            {
                if (m != 0)
                {
                    if (q.y() < clipper->value(3))
                    {
                        float x = (clipper->value(3) - q.y()) / m + q.x();
                        if (clipper->value(0) <= x && x <= clipper->value(1))
                        {
                            if (j == 1)
                            {
                                r1 = QPoint(round(x), clipper->value(3));
                                a(&j, r1, r2, clipper, pr, q, line, m);
                            }
                            else
                            {
                                r2 = QPoint(round(x), clipper->value(3));
                                a(&j, r1, r2, clipper, pr, q, line, m);
                            }
                        }
                        if (q.y() > clipper->value(2))
                        {
                            x = (clipper->value(2) - q.y())/m + q.x();
                            if (clipper->value(0) <= x && x <= clipper->value(1))
                            {
                                if (j == 1)
                                {
                                    r1 = QPoint(round(x), clipper->value(2));
                                    a(&j, r1, r2, clipper, pr, q, line, m);
                                }
                                else
                                {
                                    r2 = QPoint(round(x), clipper->value(2));
                                    a(&j, r1, r2, clipper, pr, q, line, m);
                                }
                            }
                            return;
                        }
                    }
                    if (q.y() > clipper->value(2))
                    {
                        float x = (clipper->value(2) - q.y())/m + q.x();
                        if (clipper->value(0) <= x && x <= clipper->value(1))
                        {
                            if (j == 1)
                            {
                                r1 = QPoint(round(x), clipper->value(2));
                                a(&j, r1, r2, clipper, pr, q, line, m);
                            }
                            else
                            {
                                r2 = QPoint(round(x), clipper->value(2));
                                a(&j, r1, r2, clipper, pr, q, line, m);
                            }
                        }
                        return;
                    }
                }
                return;
            }
            m = (line.y2() - line.y1())/(line.x2() - line.x1());
            if (q.x() < clipper->value(0))
            {
                float y = m * (clipper->value(0) - q.x()) + q.y();
                if (clipper->value(3) <= y && y <= clipper->value(2))
                {
                    if (j == 1)
                    {
                        r1 = QPoint(clipper->value(0), round(y));
                        a(&j, r1, r2, clipper, pr, q, line, m);
                    }
                    else
                    {
                        r2 = QPoint(clipper->value(0), round(y));
                        a(&j, r1, r2, clipper, pr, q, line, m);
                    }
                }
                if (q.x() > clipper->value(1))
                {
                    float y = m * (clipper->value(1) - q.x()) + q.y();
                    if (clipper->value(3) <= y && y <= clipper->value(2))
                    {
                        if (j == 1)
                        {
                            r1 = QPoint(clipper->value(1), round(y));
                            a(&j, r1, r2, clipper, pr, q, line, m);
                        }
                        else
                        {
                            r2 = QPoint(clipper->value(1), round(y));
                            a(&j, r1, r2, clipper, pr, q, line, m);
                        }
                    }
                }
                if (m != 0)
                {
                    if (q.y() < clipper->value(3))
                    {
                        float x = (clipper->value(3) - q.y()) / m + q.x();
                        if (clipper->value(0) <= x && x <= clipper->value(1))
                        {
                            if (j == 1)
                            {
                                r1 = QPoint(round(x), clipper->value(3));
                                a(&j, r1, r2, clipper, pr, q, line, m);
                            }
                            else
                            {
                                r2 = QPoint(round(x), clipper->value(3));
                                a(&j, r1, r2, clipper, pr, q, line, m);
                            }
                        }
                        if (q.y() > clipper->value(2))
                        {
                            x = (clipper->value(2) - q.y())/m + q.x();
                            if (clipper->value(0) <= x && x <= clipper->value(1))
                            {
                                if (j == 1)
                                {
                                    r1 = QPoint(round(x), clipper->value(2));
                                    a(&j, r1, r2, clipper, pr, q, line, m);
                                }
                                else
                                {
                                    r2 = QPoint(round(x), clipper->value(2));
                                    a(&j, r1, r2, clipper, pr, q, line, m);
                                }
                            }
                            return;
                        }
                    }
                    if (q.y() > clipper->value(2))
                    {
                        float x = (clipper->value(2) - q.y())/m + q.x();
                        if (clipper->value(0) <= x && x <= clipper->value(1))
                        {
                            if (j == 1)
                            {
                                r1 = QPoint(round(x), clipper->value(2));
                                a(&j, r1, r2, clipper, pr, q, line, m);
                            }
                            else
                            {
                                r2 = QPoint(round(x), clipper->value(2));
                                a(&j, r1, r2, clipper, pr, q, line, m);
                            }
                        }
                        return;
                    }
                }
                return;
            }
            if (q.x() > clipper->value(1))
            {
                float y = m * (clipper->value(1) - q.x()) + q.y();
                if (clipper->value(3) <= y && y <= clipper->value(2))
                {
                    if (j == 1)
                    {
                        r1 = QPoint(clipper->value(1), round(y));
                        a(&j, r1, r2, clipper, pr, q, line, m);
                    }
                    else
                    {
                        r2 = QPoint(clipper->value(1), round(y));
                        a(&j, r1, r2, clipper, pr, q, line, m);
                    }
                }
            }
            if (m != 0)
            {
                if (q.y() < clipper->value(3))
                {
                    float x = (clipper->value(3) - q.y()) / m + q.x();
                    if (clipper->value(0) <= x && x <= clipper->value(1))
                    {
                        if (j == 1)
                        {
                            r1 = QPoint(round(x), clipper->value(3));
                            a(&j, r1, r2, clipper, pr, q, line, m);
                        }
                        else
                        {
                            r2 = QPoint(round(x), clipper->value(3));
                            a(&j, r1, r2, clipper, pr, q, line, m);
                        }
                    }
                    if (q.y() > clipper->value(2))
                    {
                        x = (clipper->value(2) - q.y())/m + q.x();
                        if (clipper->value(0) <= x && x <= clipper->value(1))
                        {
                            if (j == 1)
                            {
                                r1 = QPoint(round(x), clipper->value(2));
                                a(&j, r1, r2, clipper, pr, q, line, m);
                            }
                            else
                            {
                                r2 =QPoint(round(x), clipper->value(2));
                                a(&j, r1, r2, clipper, pr, q, line, m);
                            }
                        }
                        return;
                    }
                }
                if (q.y() > clipper->value(2))
                {
                    float x = (clipper->value(2) - q.y())/m + q.x();
                    if (clipper->value(0) <= x && x <= clipper->value(1))
                    {
                        if (j == 1)
                        {
                            r1 = QPoint(round(x), clipper->value(2));
                            a(&j, r1, r2, clipper, pr, q, line, m);
                        }
                        else
                        {
                            r2 = QPoint(round(x), clipper->value(2));
                            a(&j, r1, r2, clipper, pr, q, line, m);
                        }
                    }
                    return;
                }
            }
        }
    j = 0;
    a(&j, r1, r2, clipper, pr, q, line, m);

}
}

void MainWindow::a(int *j, QPoint r1, QPoint r2, QVector<int> *clipper, bool pr, QPoint q, QLine line, float m)
{
    *j += 1;
    if (*j > 2)
    {
        put_line(r1, r2, pr);//!!!!!!!!!!!!!!!!!!!!!!!!!!!
        return;
    }
    if (*j == 1)
        q = line.p1();
    else
        q = line.p2();
    if (line.x1() == line.x2())
    {
        if (m != 0)
        {
            if (q.y() < clipper->value(3))
            {
                float x = (clipper->value(3) - q.y()) / m + q.x();
                if (clipper->value(0) <= x && x <= clipper->value(1))
                {
                    if (*j == 1)
                    {
                        r1 = QPoint(round(x), clipper->value(3));
                        a(j, r1, r2, clipper, pr, q, line, m);
                    }
                    else if (*j == 2)
                    {
                        r2 = QPoint(round(x), clipper->value(3));
                        a(j, r1, r2, clipper, pr, q, line, m);
                    }
                }
                if (q.y() > clipper->value(2))
                {
                    x = (clipper->value(2) - q.y())/m + q.x();
                    if (clipper->value(0) <= x && x <= clipper->value(1))
                    {
                        if (*j == 1)
                        {
                            r1 = QPoint(round(x), clipper->value(2));
                            a(j, r1, r2, clipper, pr, q, line, m);
                        }
                        else if (*j == 2)
                        {
                            r2 = QPoint(round(x), clipper->value(2));
                            a(j, r1, r2, clipper, pr, q, line, m);
                        }
                    }
                    return;
                }
            }
            if (q.y() > clipper->value(2))
            {
                float x = (clipper->value(2) - q.y())/m + q.x();
                if (clipper->value(0) <= x && x <= clipper->value(1))
                {
                    if (*j == 1)
                    {
                        r1 = QPoint(round(x), clipper->value(2));
                        a(j, r1, r2, clipper, pr, q, line, m);
                    }
                    else
                    {
                        r2 = QPoint(round(x), clipper->value(2));
                        a(j, r1, r2, clipper, pr, q, line, m);
                    }
                }
                return;
            }
        }
        return;
    }
    m = (line.y2() - line.y1())/(line.x2() - line.x1());
    if (q.x() < clipper->value(0))
    {
        float y = m * (clipper->value(0) - q.x()) + q.y();
        if (clipper->value(3) <= y && y <= clipper->value(2))
        {
            if (*j == 1)
            {
                r1 = QPoint(clipper->value(0), round(y));
                a(j, r1, r2, clipper, pr, q, line, m);
            }
            else
            {
                r2 = QPoint(clipper->value(0), round(y));
                a(j, r1, r2, clipper, pr, q, line, m);
            }
        }
        if (q.x() > clipper->value(1))
        {
            float y = m * (clipper->value(1) - q.x()) + q.y();
            if (clipper->value(3) <= y && y <= clipper->value(2))
            {
                if (*j == 1)
                {
                    r1 = QPoint(clipper->value(1), round(y));
                    a(j, r1, r2, clipper, pr, q, line, m);
                }
                else
                {
                    r2 = QPoint(clipper->value(1), round(y));
                    a(j, r1, r2, clipper, pr, q, line, m);
                }
            }
        }
        if (m != 0)
        {
            if (q.y() < clipper->value(3))
            {
                float x = (clipper->value(3) - q.y()) / m + q.x();
                if (clipper->value(0) <= x && x <= clipper->value(1))
                {
                    if (*j == 1)
                    {
                        r1 = QPoint(round(x), clipper->value(3));
                        a(j, r1, r2, clipper, pr, q, line, m);
                    }
                    else
                    {
                        r2 = QPoint(round(x), clipper->value(3));
                        a(j, r1, r2, clipper, pr, q, line, m);
                    }
                }
                if (q.y() > clipper->value(2))
                {
                    x = (clipper->value(2) - q.y())/m + q.x();
                    if (clipper->value(0) <= x && x <= clipper->value(1))
                    {
                        if (*j == 1)
                        {
                            r1 = QPoint(round(x), clipper->value(2));
                            a(j, r1, r2, clipper, pr, q, line, m);
                        }
                        else
                        {
                            r2 = QPoint(round(x), clipper->value(2));
                            a(j, r1, r2, clipper, pr, q, line, m);
                        }
                    }
                    return;
                }
            }
            if (q.y() > clipper->value(2))
            {
                float x = (clipper->value(2) - q.y())/m + q.x();
                if (clipper->value(0) <= x && x <= clipper->value(1))
                {
                    if (*j == 1)
                    {
                        r1 = QPoint(round(x), clipper->value(2));
                        a(j, r1, r2, clipper, pr, q, line, m);
                    }
                    else
                    {
                        r2 = QPoint(round(x), clipper->value(2));
                        a(j, r1, r2, clipper, pr, q, line, m);
                    }
                }
                return;
            }
        }
        return;
    }
    if (q.x() > clipper->value(1))
    {
        float y = m * (clipper->value(1) - q.x()) + q.y();
        if (clipper->value(3) <= y && y <= clipper->value(2))
        {
            if (*j == 1)
            {
                r1 = QPoint(clipper->value(1), round(y));
                a(j, r1, r2, clipper, pr, q, line, m);
            }
            else
            {
                r2 = QPoint(clipper->value(1), round(y));
                a(j, r1, r2, clipper, pr, q, line, m);
            }
        }
    }
    if (m != 0)
    {
        if (q.y() < clipper->value(3))
        {
            float x = (clipper->value(3) - q.y()) / m + q.x();
            if (clipper->value(0) <= x && x <= clipper->value(1))
            {
                if (*j == 1)
                {
                    r1 = QPoint(round(x), clipper->value(3));
                    a(j, r1, r2, clipper, pr, q, line, m);
                }
                else
                {
                    r2 = QPoint(round(x), clipper->value(3));
                    a(j, r1, r2, clipper, pr, q, line, m);
                }
            }
            if (q.y() > clipper->value(2))
            {
                x = (clipper->value(2) - q.y())/m + q.x();
                if (clipper->value(0) <= x && x <= clipper->value(1))
                {
                    if (*j == 1)
                    {
                        r1 = QPoint(round(x), clipper->value(2));
                        a(j, r1, r2, clipper, pr, q, line, m);
                    }
                    else
                    {
                        r2 = QPoint(round(x), clipper->value(2));
                        a(j, r1, r2, clipper, pr, q, line, m);
                    }
                }
                return;
            }
        }
        if (q.y() > clipper->value(2))
        {
            float x = (clipper->value(2) - q.y())/m + q.x();
            if (clipper->value(0) <= x && x <= clipper->value(1))
            {
                if (*j == 1)
                {
                    r1 = QPoint(round(x), clipper->value(2));
                    a(j, r1, r2, clipper, pr, q, line, m);
                }
                else
                {
                    r2 = QPoint(round(x), clipper->value(2));
                    a(j, r1, r2, clipper, pr, q, line, m);
                }
            }
            return;
        }
    }
    return;
}
*/

void MainWindow::on_clip_clicked()
{
    img->fill(Qt::white);
    QGraphicsScene *scene = ui->graphics->scene();
    scene->clear();
    scene->addPixmap(QPixmap::fromImage(*img));
    for (int i = 0; i < lines->size(); i++)
    {
        int *t1 = (int *)calloc(4, sizeof(int));
        int *t2 = (int *)calloc(4, sizeof(int));
        QLine line = lines->value(i);
        QPoint q1 = line.p1();
        QPoint q2 = line.p2();
        QPoint p1 = q1;
        QPoint p2 = q2;
        lineCodes(line, t1, t2);

        for (int k = 0; k < 4; k++)
            qDebug() << t1[k] << t2[k];

        int fl = 0;
        float m;
        if (p2.x() == p1.x())
            fl = -1;
        else
        {
            m = (p2.y() - p1.y())/(p2.x() - p1.x());
            if (m == 0)
                fl = 1;
        }
        for (int j = 0; j <= 3; j++)
        {
            if (fl == -1)
                break;
            else if (fl == 1)
            {
                put_line(p1, p2);
                break;
            }
            if (t1[j] == t2[j])
                continue;
            if (t1[j] == 0)
            {
                QPoint t = p1;
                p1 = p2;
                p2 = t;
            }
            if (fl == -1)
            {
                put_line(QPoint(p1.x(), clipper->value(j)), p2);
                break;
            }
            if (j > 2)
                put_line(QPoint(p1.x(), round(m * (clipper->value(j) - p1.x()) + p1.y())), p2);
            else
                put_line(QPoint(round((clipper->value(j) - p1.y())/m + p1.x()), p1.y()), p2);
            break;
        }
        free(t1);
        free(t2);
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

void MainWindow::lineCodes(QLine line, int *t1, int *t2)
{
    if (line.x1() < clipper->value(0))
        t1[0] = 1;
    if (line.x1() > clipper->value(1))
        t1[1] = 1;
    if (line.y1() < clipper->value(2))
        t1[2] = 1;
    if (line.y1() > clipper->value(3))
        t1[3] = 1;

    if (line.x2() < clipper->value(0))
        t2[0] = 1;
    if (line.x2() > clipper->value(1))
        t2[1] = 1;
    if (line.y2() < clipper->value(2))
        t2[2] = 1;
    if (line.y2() > clipper->value(3))
        t2[3] = 1;
}
