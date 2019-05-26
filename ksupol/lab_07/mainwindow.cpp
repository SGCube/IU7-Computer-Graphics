#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "check.h"
#include <QMessageBox>

MainWindow::MainWindow(QImage *image, QVector<QLine> *segments,
                       Paint *p, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    paint(p),
    img(image),
    lines(segments)
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
