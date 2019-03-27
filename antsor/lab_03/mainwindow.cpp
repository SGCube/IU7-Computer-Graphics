#include <QMessageBox>
#include <QPainter>

#include <math.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "point.h"
#include "draw.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	scene(0, 0, 640, 640),
	img(640, 640, QImage::Format_RGB32),
	color(255, 0, 0)
{
	ui->setupUi(this);
	ui->gView->setScene(&scene);
	
	img.fill(QColor(255, 255, 255));
	scene.addPixmap(QPixmap::fromImage(img));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_drawLineBtn_released()
{
	QString x1str = ui->x1Edit->text();
	QString y1str = ui->y1Edit->text();
	QString x2str = ui->x2Edit->text();
	QString y2str = ui->y2Edit->text();
	
	bool correct = true;
	x1 = x1str.toDouble(&correct);
	if (!correct)
	{
		QMessageBox::critical(this, "Ошибка",
							  "Некорректное значение x начальной точки!");
		return;
	}
	y1 = y1str.toDouble(&correct);
	if (!correct)
	{
		QMessageBox::critical(this, "Ошибка",
							  "Некорректное значение y начальной точки!");
		return;
	}
	x2 = x2str.toDouble(&correct);
	if (!correct)
	{
		QMessageBox::critical(this, "Ошибка",
							  "Некорректное значение x конечной точки!");
		return;
	}
	y2 = y2str.toDouble(&correct);
	if (!correct)
	{
		QMessageBox::critical(this, "Ошибка",
							  "Некорректное значение y конечной точки!");
		return;
	}
	
	QPainter painter(&img);
	QPen pen(color);
	
	if (ui->algBox->currentIndex() == 0)
		draw_line_dda(&img, Point(x1, y1), Point(x2, y2), color);
	else if (ui->algBox->currentIndex() == 4)
	{
		painter.setPen(pen);
		painter.drawLine(x1, y1, x2, y2);
	}
	
	scene.addPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_bgcolBtn_released()
{
    color.setRgb(255, 255, 255);
}

void MainWindow::on_clearButton_released()
{
    scene.clear();
	img.fill(QColor(255, 255, 255));
	scene.addPixmap(QPixmap::fromImage(img));
}
