#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "check.h"
#include <QGraphicsScene>
#include <QDebug>

#include <QtCore/QLine>
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Лабораторная работа №5");

    scene = new QGraphicsScene(this);
    ui->graphics->setScene(scene);

    ui->graphics->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphics->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    mDrawMode = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        mDrawMode = true;
        mDrawBuffer.append(event->pos());
        event->accept();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        mDrawMode = false;
        mDrawBuffer.append(event->pos());
        this->update();
        event->accept();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (!mDrawMode) return;
    mDrawBuffer.append(event->pos());
    this->update();
    event->accept();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    if (mDrawBuffer.size()<2) return;
    /*
    QPainter painter(this);
    painter.setPen(Qt::green);
    QList<QPoint>::const_iterator it = mDrawBuffer.begin();
    QPoint start = *it;
    it++;
    while(it != mDrawBuffer.end())
    {
        QPoint end = *it;
        painter.drawLine(start,end);
        start = end;
        it++;
    }
    */
    qDebug() << mDrawBuffer.begin();
}
