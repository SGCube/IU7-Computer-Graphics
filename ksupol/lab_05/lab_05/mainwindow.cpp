#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "check.h"
#include <QGraphicsScene>
#include <QColorDialog>
#include <QColor>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QPainter>

MainWindow::MainWindow(QImage *image, QVector<QVector<QPoint>> *polygons, QVector<QPoint> *pol,
                       Paint *p, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    img(image),
    polygons_kit(polygons),
    polygon(pol),
    paint(p)
{
    ui->setupUi(this);
    this->setWindowTitle("Лабораторная работа №5");

    ui->graphics->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphics->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphics->setMouseTracking(true);

    const QStringList a = {"X", "Y"};
    ui->table->setColumnCount(2);
    ui->table->setShowGrid(true);
    ui->table->setHorizontalHeaderLabels(a);
    ui->table->horizontalHeader()->resizeSection(0, 80);
    ui->table->horizontalHeader()->resizeSection(1, 80);
    ui->table->setEditTriggers(QAbstractItemView :: NoEditTriggers);
    ui->table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pen.setWidth(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::add_scene(QGraphicsScene *scene)
{
    ui->graphics->setScene(scene);
}

void MainWindow::on_add_point_clicked()
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
    int b = ui->col_b->currentIndex();
    if (polygon->size() == 1)
        check_b = b;
    else
    {
        if (b != check_b)
        {
            QMessageBox::critical(this, "Ошибка", "Вы пока не можете менять цвет границы!");
            b = check_b;
            ui->col_b->setCurrentIndex(b);
        }
    }
    QPoint a;
    a.setX(x);
    a.setY(y);
    polygon->push_back(a);
    paint->begin(img);
    paint->color(b);
    if (polygon->size() > 1)
    {
        int index = polygon->size() - 2;
        QPoint last = polygon->value(index);
        paint->drawLine(last.x(), last.y(), x, y);
    }
    QGraphicsScene *scene = ui->graphics->scene();
    scene->addPixmap(QPixmap::fromImage(*img));

    paint->end();

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

void MainWindow::on_clear_clicked()
{
    QGraphicsScene *scene = ui->graphics->scene();
    scene->clear();
}

void MainWindow::on_lock_clicked()
{
    if (polygon->size() < 3)
    {
        QMessageBox::critical(this, "Ошибка", "Недостаточно точек, чтобы замкнуть фигуру!");
        return;
    }
    int x = polygon->value(0).x();
    int y = polygon->value(0).y();
    insert_into_table(QString::number(x), QString::number(y));

    paint->begin(img);
    paint->setPen(pen);
    int index = polygon->size() - 1;
    QPoint last = polygon->value(index);
    paint->drawLine(last.x(), last.y(), x, y);

    QGraphicsScene *scene = ui->graphics->scene();
    scene->addPixmap(QPixmap::fromImage(*img));

    paint->end();

    insert_into_table("X", "Y");

    polygons_kit->push_back(*polygon);
    polygon->clear();
}

void MainWindow::on_clear_table_clicked()
{
    int row = ui->table->rowCount();
    do
    {
        ui->table->removeRow(row - 1);
        row--;
    }
    while (row > 0);
    QGraphicsScene *scene = ui->graphics->scene();
    scene->clear();
    polygon->clear();
    polygons_kit->clear();
}

void MainWindow::on_fill_clicked()
{
    if (polygons_kit->size() == 0)
    {
        QMessageBox::critical(this, "Ошибка", "Нет фигуры!");
        return;
    }
    if (polygon->size() != 0)
    {
        QMessageBox::critical(this, "Ошибка", "Необходимо замкнуть фигуру!");
        return;
    }
    int f = ui->col_f->currentIndex();
    int b = ui->col_b->currentIndex();
    QVector<QPoint> first = polygons_kit->value(0);
    int xmin = first.value(0).x();
    int xmax = first.value(0).x();
    int ymin = first.value(0).y();
    int ymax = first.value(0).y();
    for (int i = 1; i < first.size(); i++)
    {
        if (first.value(i).x() < xmin)
            xmin = first.value(i).x();
        if (first.value(i).x() > xmax)
            xmax = first.value(i).x();
        if (first.value(i).y() < ymin)
            ymin = first.value(i).y();
        if (first.value(i).y() > ymax)
            ymax = first.value(i).y();
    }
    QColor border;
    QColor fill;
    QColor ground = Qt::white;
    set_color(&border, b);
    set_color(&fill, f);
    qDebug() << border << fill;

    bool flag = false;
    for (int y = ymax; y >= ymin; y--)
    {
        for (int x = xmin; x <= xmax; x++)
        {
            if (img->pixelColor(x, y) == border)
            {
                if (flag == false)
                    flag = true;
                else
                    flag = false;
            }
            if (flag == true)
                img->setPixelColor(x, y, fill);
            else
                img->setPixelColor(x, y, ground);
        }
    }
    QGraphicsScene *scene = ui->graphics->scene();
    scene->addPixmap(QPixmap::fromImage(*img));
}
