#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "check.h"
#include "list.h"
#include <QLineEdit>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QtCore>
#include <qmath.h>
#include <QGraphicsTextItem>

point *head = NULL;
tri *head_res = NULL;
int amount = 0;

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
    ui->table->horizontalHeader()->resizeSection(0, 157);
    ui->table->horizontalHeader()->resizeSection(1, 157);
    ui->table->setEditTriggers(QAbstractItemView :: NoEditTriggers);
    ui->graphics->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphics->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

MainWindow::~MainWindow()
{
    clear_list();
    delete ui;
}
void MainWindow::on_enter_clicked()
{
    scene->clear();
    int check = 0;
    if (ui->lineEditX->text() == NULL && ui->lineEditY->text() == NULL)
    {
        QMessageBox::critical(this, "Ошибка","Необходимо"
                                   " ввести координаты X и Y!");
        return;
    }
    if (ui->lineEditX->text() == NULL && ui->lineEditY->text() != NULL)
    {
        QMessageBox::critical(this, "Ошибка","Необходимо"
                                   " ввести координату X!");
        return;
    }
    if (ui->lineEditX->text() != NULL && ui->lineEditY->text() == NULL)
    {
        QMessageBox::critical(this, "Ошибка","Необходимо"
                                   " ввести координату Y!");
        return;
    }
    QString x_str = ui->lineEditX->text();
    QString y_str = ui->lineEditY->text();
    check = check_point(x_str);
    if (check == -1)
    {
        QMessageBox::critical(this, "Ошибка","Неккоректная"
                                   " координата X!");
        return;
    }
    check =check_point(y_str);
    if (check == -1)
    {
        QMessageBox::critical(this, "Ошибка","Неккоректная"
                                   " координата Y!");
        return;
    }

    float x_fl = x_str.toFloat();
    float y_fl = y_str.toFloat();

    insert_into_table(x_str, y_str);
    head = add_to_list(head, x_fl, y_fl);
    if (head == NULL)
    {
        QMessageBox::critical(this, "Ошибка","Ошибка выделения памяти!");
        return;
    }
    amount++;
    ui->lineEditX->clear();
    ui->lineEditY->clear();
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

void MainWindow::on_change_clicked()
{
    scene->clear();
    int check = 0;
    if (ui->lineEdit_change->text() == NULL)
    {
        QMessageBox::critical(this, "Ошибка","Введите номер точки!");
        ui->lineEdit_change->clear();
        return;
    }
    QString a = ui->lineEdit_change->text();
    for (int i = 0; i < a.length(); i++)
    {
        if (a[i] > '9' || a[i] < '0')
        {
            QMessageBox::critical(this, "Ошибка","Введите корректный номер точки!");
            ui->lineEdit_change->clear();
            return;
        }
    }
    int a_int = a.toInt();
    if (a_int > amount || a_int == 0)
    {
        QMessageBox::critical(this, "Ошибка","Такой точки нет!");
        ui->lineEdit_change->clear();
        return;
    }
    if (ui->lineEditX->text() == NULL && ui->lineEditY->text() == NULL)
    {
        QMessageBox::critical(this, "Ошибка","Необходимо"
                                   " ввести новые координаты X и Y!");
        return;
    }
    if (ui->lineEditX->text() == NULL && ui->lineEditY->text() != NULL)
    {
        QMessageBox::critical(this, "Ошибка","Необходимо"
                                   " ввести новую координату X!");
        return;
    }
    if (ui->lineEditX->text() != NULL && ui->lineEditY->text() == NULL)
    {
        QMessageBox::critical(this, "Ошибка","Необходимо"
                                   " ввести новую координату Y!");
        return;
    }
    QString new_x = ui->lineEditX->text();
    QString new_y = ui->lineEditY->text();
    check = check_point(new_x);
    if (check == -1)
    {
        QMessageBox::critical(this, "Ошибка","Неккоректная"
                                   " координата X!");
        return;
    }
    check = check_point(new_y);
    if (check == -1)
    {
        QMessageBox::critical(this, "Ошибка","Неккоректная"
                                   " координата Y!");
        return;
    }
    head = change_element(head, a_int, new_x, new_y);
    change_table(a_int, new_x, new_y);
    ui->lineEditX->clear();
    ui->lineEditY->clear();
    ui->lineEdit_change->clear();
}

void MainWindow::change_table(int a_int, QString new_x, QString new_y)
{
    if (a_int == 1)
    {
        ui->table->removeRow(0);
        ui->table->insertRow(0);
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setText(new_x);
        ui->table->setItem(0,0,item);
        QTableWidgetItem *item2 = new QTableWidgetItem();
        item2->setText(new_y);
        ui->table->setItem(0,1,item2);
        return;
    }
    ui->table->removeRow(a_int - 1);
    ui->table->insertRow(a_int - 1);
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setText(new_x);
    ui->table->setItem(a_int - 1,0,item);
    QTableWidgetItem *item2 = new QTableWidgetItem();
    item2->setText(new_y);
    ui->table->setItem(a_int - 1,1,item2);
    return;
}

void MainWindow::on_delet_clicked()
{
    scene->clear();
    if (ui->lineEdit_change->text() == NULL)
    {
        QMessageBox::critical(this, "Ошибка","Введите номер точки!");
        return;
    }
    QString d = ui->lineEdit_change->text();
    for (int i = 0; i < d.length(); i++)
    {
        if (d[i] > '9' || d[i] < '0')
        {
            QMessageBox::critical(this, "Ошибка","Введите корректный номер точки!");
            ui->lineEdit_change->clear();
            return;
        }
    }
    int d_int = d.toInt();
    if (d_int > amount || d_int == 0)
    {
        QMessageBox::critical(this, "Ошибка","Такой точки нет!");
        ui->lineEdit_change->clear();
        return;
    }
    ui->table->removeRow(d_int - 1);
    head = delete_from_list(head, d_int);
    ui->lineEdit_change->clear();
    amount--;
}

void MainWindow::on_delete_all_clicked()
{
    scene->clear();
    while (amount >= 0)
    {
        ui->table->removeRow(amount);
        amount--;
    }
    clear_list();
    amount = 0;
}

void MainWindow::on_show_clicked()
{
    if (amount < 3)
    {
        QMessageBox::critical(this, "Ошибка","Слишком мало точек!");
        return;
    }
    clear_list_res();
    find_result();
}

void MainWindow::find_result()
{
    point *a = head, *b = head->next, *c = head->next->next;
    int ch = 0;
    float min = diff(a->x, a->y, b->x, b->y, c->x, c->y);

    while (a->next->next != NULL)
    {
        while (b->next != NULL)
        {
            while (c != NULL)
            {
                if (check_tr(a->x, a->y, b->x, b->y, c->x, c->y) != 0)
                    ch ++;
                else
                {
                    float t = diff(a->x, a->y, b->x, b->y, c->x, c->y);
                    if (t < min)
                        min = t;
                }
                c = c->next;
            }
            b = b->next;
            c = b->next;
        }
        a = a->next;
        b = a->next;
        c = b->next;
    }
    int k = 1;
    for (int i = 1; i <= amount; i++)
        k *= i;
    int n = 1;
    for (int i = 1; i<= amount - 3; i++)
        n *= i;
    if (ch == k / 6 * n)
    {
        QMessageBox::critical(this, "Ошибка","Все треугольники вырождены!");
        return;
    }
    a = head;
    b = head->next;
    c = head->next->next;
    while (a->next->next != NULL)
    {
        while (b->next != NULL)
        {
            while (c != NULL)
            {
                if (check_tr(a->x, a->y, b->x, b->y, c->x, c->y) != 0)
                    ch ++;
                else
                {
                    float t = diff(a->x, a->y, b->x, b->y, c->x, c->y);
                    if (t == min)
                    {
                        head_res = insert_in_res(head_res, a->x, a->y, b->x, b->y, c->x, c->y);
                        if (head_res == NULL)
                        {
                            QMessageBox::critical(this, "Ошибка","Ошибка выделения памяти!");
                            return;
                        }
                    }
                }
                c = c->next;
            }
            b = b->next;
            c = b->next;
        }
        a = a->next;
        b = a->next;
        c = b->next;
    }
    draw_result(head_res);
}

float MainWindow::diff(float x1, float y1, float x2, float y2, float x3, float y3)
{
    float a = sqrt(qPow(x2 - x1, 2) + qPow(y2 - y1, 2));
    float b = sqrt(qPow(x3 - x1, 2) + qPow(y3 - y1, 2));
    float c = sqrt(qPow(x3 - x2, 2) + qPow(y3 - y2, 2));
    if (a == b && a == c && b == c)
        return 0;

    float ad = c * b / (a + c);
    float eb = c * a / (b + a);
    float fc = b * a / (b + c);
    float dc = a * b / (c + a);
    float ae = c * b / (b + a);
    float bf = a * c / (b + c);

    float max = qMax(qMax(qMax(ad, eb), qMax(fc, dc)), qMax(bf, ae));
    float min = qMin(qMin(qMin(ad, eb), qMin(fc, dc)), qMin(bf, ae));
    return max - min;
}

void MainWindow::draw_result(tri *head_res)
{
    scene->clear();
    QBrush redBrush(Qt::red);
    QPen blueBrush(Qt::blue);
    QPen blackpen(Qt::black);
    blackpen.setWidth(3);
    blueBrush.setWidth(3);

    tri *res = head_res;

    float xmin = 0;
    float xmax = 0;
    float ymin = 0;
    float ymax = 0;
    if (res != NULL)
    {
        xmin = qMin(res->x1, qMin(res->x2, res->x3));
        xmax = qMax(res->x1, qMax(res->x2, res->x3));
        ymin = qMin(res->y1, qMin(res->y2, res->y3));
        ymax = qMax(res->y1, qMax(res->y2, res->y3));

    }
    while(res != NULL)
    {
        float xmin_cur = qMin(res->x1, qMin(res->x2, res->x3));
        if (xmin_cur < xmin)
            xmin = xmin_cur;
        float xmax_cur = qMax(res->x1, qMax(res->x2, res->x3));
        if (xmax_cur > xmax)
            xmax = xmax_cur;
        float ymin_cur = qMin(res->y1, qMin(res->y2, res->y3));
        if (ymin_cur < ymin)
            ymin = ymin_cur;
        float ymax_cur = qMax(res->y1, qMax(res->y2, res->y3));
        if (ymax_cur > ymax)
            ymax = ymax_cur;
        res = res->next;
    }
    res = head_res;
    while (res != NULL)
    {
        float w = xmax - xmin;
        float h = ymax - ymin;

        float k = qMin(800 / w, 500 / h);

        float x1 = k * res->x1 + (1 - k) * 400;
        float x2 = k * res->x2 + (1 - k) * 400;
        float x3 = k * res->x3 + (1 - k) * 400;
        float y1 = k * res->y1 + (1 - k) * (-250);
        float y2 = k * res->y2 + (1 - k) * (-250);
        float y3 = k * res->y3 + (1 - k) * (-250);
        float x = 400 - w / 2 - xmin;
        float y = -250 - h / 2 - ymin;
        scene->addLine(x1 + k*x, -y1 - k*y, x2 + k*x, -y2 - k*y, blackpen);
        scene->addLine(x1 + k*x, -y1 - k*y, x3 + k*x, -y3 - k*y, blackpen);
        scene->addLine(x3 + k*x, -y3 - k*y, x2 + k*x, -y2 - k*y, blackpen);

        float a = sqrt(qPow(res->x2 - res->x1, 2) + qPow(res->y2 - res->y1, 2));
        float b = sqrt(qPow(res->x3 - res->x1, 2) + qPow(res->y3 - res->y1, 2));
        float c = sqrt(qPow(res->x3 - res->x2, 2) + qPow(res->y3 - res->y2, 2));

        float xx1 = res->x2 - res->x1;
        float yy1 = res->y2 - res->y1;
        float fc = b * a / (b + c);
        float kk1 = sqrt(qPow(fc, 2)/(qPow(xx1, 2) + qPow(yy1, 2)));
        float x01 = kk1 * xx1 + res->x1;
        float y01 = kk1 * yy1 + res->y1;
        float x_b_1 = k * x01 + (1 - k) * 400;
        float y_b_1 = k * y01 + (1 - k) * (-250);
        scene->addLine(x_b_1 + k*x, -y_b_1 - k*y, x3 + k*x, -y3 - k*y, blueBrush);

        float xx2 = res->x3 - res->x1;
        float yy2 = res->y3 - res->y1;
        float dc = a * b / (c + a);
        float kk2 = sqrt(qPow(dc, 2)/(qPow(xx2, 2) + qPow(yy2, 2)));
        float x02 = kk2 * xx2 + res->x1;
        float y02 = kk2 * yy2 + res->y1;
        float x_b_2 = k * x02 + (1 - k) * 400;
        float y_b_2 = k * y02 + (1 - k) * (-250);
        scene->addLine(x_b_2 + k*x, -y_b_2 - k*y, x2 + k*x, -y2 - k*y, blueBrush);

        float xx3 = res->x3 - res->x2;
        float yy3 = res->y3 - res->y2;
        float eb = c * a / (b + a);
        float kk3 = sqrt(qPow(eb, 2)/(qPow(xx3, 2) + qPow(yy3, 2)));
        float x03 = kk3 * xx3 + res->x2;
        float y03 = kk3 * yy3 + res->y2;
        float x_b_3 = k * x03 + (1 - k) * 400;
        float y_b_3 = k * y03 + (1 - k) * (-250);
        scene->addLine(x_b_3 + k*x, -y_b_3 - k*y, x1 + k*x, -y1 - k*y, blueBrush);

        put_text(res, x1+k*x, -y1-k*y, x2+k*x, -y2-k*y, x3+k*x, -y3-k*y);
        res = res->next;
    }
}

void MainWindow::put_text(tri *res, float x1, float y1, float x2, float y2, float x3, float y3)
{
    QFont font = QFont("sans", 12);
    QString str;
    QGraphicsTextItem *label;
    int number = find_number(head, res->x1, res->y1);
    str = "Точка №" + QString::number(number) + "(" + QString::number(res->x1) +
                        ", " + QString::number(res->y1) + ")";
    label = scene->addText(str, font);
    label->setX(x1);
    label->setY(y1);

    number = find_number(head, res->x2, res->y2);
    str = "Точка №" + QString::number(number) + "(" + QString::number(res->x2) +
                        ", " + QString::number(res->y2) + ")";
    label = scene->addText(str, font);
    label->setX(x2);
    label->setY(y2);

    number = find_number(head, res->x3, res->y3);
    str = "Точка №" + QString::number(number) + "(" + QString::number(res->x3) +
                        ", " + QString::number(res->y3) + ")";
    label = scene->addText(str, font);
    label->setX(x3);
    label->setY(y3);
}
