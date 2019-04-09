#include <QMessageBox>
#include <QColorDialog>
#include <QPainter>
#include <QtMath>

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

void MainWindow::on_drawLineBtn_released()
{
	QString x1str = ui->x1Edit->text();
	QString y1str = ui->y1Edit->text();
	QString x2str = ui->x2Edit->text();
	QString y2str = ui->y2Edit->text();
	
	bool correct = true;
	x1 = x1str.toInt(&correct);
	if (!correct)
	{
		QMessageBox::critical(this, "Ошибка",
							  "Некорректное значение x начальной точки!");
		return;
	}
	y1 = y1str.toInt(&correct);
	if (!correct)
	{
		QMessageBox::critical(this, "Ошибка",
							  "Некорректное значение y начальной точки!");
		return;
	}
	x2 = x2str.toInt(&correct);
	if (!correct)
	{
		QMessageBox::critical(this, "Ошибка",
							  "Некорректное значение x конечной точки!");
		return;
	}
	y2 = y2str.toInt(&correct);
	if (!correct)
	{
		QMessageBox::critical(this, "Ошибка",
							  "Некорректное значение y конечной точки!");
		return;
	}
	
	QPainter painter(&img);
	QPen pen(color);
	painter.setPen(pen);
	
	if (ui->algBox->currentIndex() == 0)
		draw_line_dda(&painter, Point(x1, y1), Point(x2, y2), color);
	else if (ui->algBox->currentIndex() == 1)
		draw_line_bres_real(&painter, Point(x1, y1), Point(x2, y2), color);
	else if (ui->algBox->currentIndex() == 2)
		draw_line_bres_int(&painter, Point(x1, y1), Point(x2, y2), color);
	else if (ui->algBox->currentIndex() == 3)
		draw_line_bres_aa(&painter, Point(x1, y1), Point(x2, y2), color);
	else if (ui->algBox->currentIndex() == 4)
		painter.drawLine(x1, y1, x2, y2);
	
	scene.addPixmap(QPixmap::fromImage(img));
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

void MainWindow::on_drawSunBtn_released()
{
	QString angle_str = ui->angleEdit->text();
	QString len_str = ui->lenEdit->text();
	
	bool correct = true;
	angle = angle_str.toInt(&correct);
	if (!correct || angle < 0)
	{
		QMessageBox::critical(this, "Ошибка",
							  "Некорректное значение угла!");
		return;
	}
	len = len_str.toDouble(&correct);
	if (!correct || len <= 0)
	{
		QMessageBox::critical(this, "Ошибка",
							  "Некорректное значение длины!");
		return;
	}
	
	void (*method)(QPainter*, Point, Point, QColor) = nullptr;
	
	QPainter painter(&img);
	QPen pen(color);
	painter.setPen(pen);
	
	if (ui->algBox->currentIndex() == 0)
		method = draw_line_dda;
	else if (ui->algBox->currentIndex() == 1)
		method = draw_line_bres_real;
	else if (ui->algBox->currentIndex() == 2)
		method = draw_line_bres_int;
	else if (ui->algBox->currentIndex() == 3)
		method = draw_line_bres_aa;
	
	if (angle % 360 == 0)
		angle = 360;
	
	Point center(320, 320);
	Point endp(320, 320);
	
	for (double cur_ang = 0; cur_ang < 360; cur_ang += angle)
	{
		double rad = qDegreesToRadians(double(cur_ang));
		endp.setX(center.x() + len * qCos(rad));
		endp.setY(center.y() - len * qSin(rad));
		if (method)
			method(&painter, center, endp, color);
		else
			painter.drawLine(center.x(), center.y(),
							 endp.x(), endp.y());
	}
	
	scene.addPixmap(QPixmap::fromImage(img));
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
