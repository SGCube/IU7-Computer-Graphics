#include <QMessageBox>
#include <QColorDialog>
#include <QPainter>
#include <QtMath>

#include <math.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "point.h"
#include "line.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	scene(0, 0, 640, 640),
	img(640, 640, QImage::Format_RGB32),
	color(0, 0, 255)
{
	ui->setupUi(this);
	ui->gView->setScene(&scene);
	
	img.fill(QColor(255, 255, 255));
	scene.addPixmap(QPixmap::fromImage(img));
	
	set_colorFrame();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::set_colorFrame()
{
	QPixmap pxm(ui->colorFrame->rect().size());
	pxm.fill(color);
	ui->colorFrame->setPixmap(pxm);
}

void MainWindow::on_bgcolBtn_released()
{
    color.setRgb(255, 255, 255);
	set_colorFrame();
}

void MainWindow::on_clearButton_released()
{
    scene.clear();
	img.fill(QColor(255, 255, 255));
	scene.addPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_palletteBtn_released()
{
    QColor newcolor = QColorDialog::getColor(color, this);
	if (newcolor.isValid())
	{
		color = newcolor;
		set_colorFrame();
	}
}

void MainWindow::on_redBtn_released()
{
	color.setRgb(255, 0, 0);
	set_colorFrame();
}

void MainWindow::on_blueBtn_released()
{
	color.setRgb(0, 0, 255);
	set_colorFrame();
}

void MainWindow::on_greenBtn_released()
{
	color.setRgb(0, 255, 0);
	set_colorFrame();
}

void MainWindow::on_blackBtn_released()
{
	color.setRgb(0, 0, 0);
	set_colorFrame();
}
