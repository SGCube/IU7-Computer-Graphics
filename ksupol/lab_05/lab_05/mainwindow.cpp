#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "check.h"
#include "fill.h"
#include <QGraphicsScene>
#include <QColorDialog>
#include <QColor>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QPainter>
#include "math.h"

MainWindow::MainWindow(QImage *image, QVector<QVector<QPoint>> *polygons, QVector<QPoint> *pol,
                       Paint *p, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    paint(p),
    img(image),
    polygon(pol),
    polygons_kit(polygons)
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
    paint->set_pen();
    if (polygon->size() > 1)
    {
        int index = polygon->size() - 2;
        QPoint last = polygon->value(index);
        paint->put_line(last.x(), last.y(), x, y);
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
    polygon->clear();
    polygons_kit->clear();
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
    paint->set_pen();
    int index = polygon->size() - 1;
    QPoint last = polygon->value(index);
    paint->put_line(last.x(), last.y(), x, y);
    //paint->drawLine(last.x(), last.y(), x, y);

    QGraphicsScene *scene = ui->graphics->scene();
    scene->addPixmap(QPixmap::fromImage(*img));

    paint->end();

    insert_into_table("X", "Y");

    polygons_kit->push_back(*polygon);
    polygon->clear();
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
    QColor border_color;
    QColor fill_color;
    QColor bg_color = Qt::white;
    set_color(&border_color, b);
    set_color(&fill_color, f);
    QGraphicsScene *scene = ui->graphics->scene();
    bool delay = ui->delay->isChecked();
    border_handling(img, scene, polygons_kit, border_color);
    filling(img, scene, polygons_kit, border_color, fill_color, bg_color, delay);
}

void MainWindow::on_col_b_currentIndexChanged(int index)
{
    paint->color(index);
}
