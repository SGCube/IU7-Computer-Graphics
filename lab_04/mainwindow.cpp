#include <QMessageBox>
#include <QColorDialog>
#include <QPainter>
#include <QtMath>

#include <math.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "line.h"
#include "circle.h"
#include "ellipse.h"

#define CANVAS_W 640
#define CANVAS_H 640

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
	
	draw_circle = draw_circle_canon;
	draw_ellipse = draw_ellipse_canon;
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

void MainWindow::on_centerBtn_released()
{
    ui->xcEdit->setText(QString::number(CANVAS_W / 2));
	ui->ycEdit->setText(QString::number(CANVAS_H / 2));
}

void MainWindow::on_centereBtn_released()
{
	ui->xceEdit->setText(QString::number(CANVAS_W / 2));
	ui->yceEdit->setText(QString::number(CANVAS_H / 2));
}

void MainWindow::on_drawCircleBtn_released()
{
	QString xstr = ui->xcEdit->text();
	QString ystr = ui->ycEdit->text();
	QString rstr = ui->radEdit->text();
	
	bool correct = true;
	xc = xstr.toInt(&correct);
	if (!correct)
	{
		QMessageBox::critical(this, "Ошибка",
							  "Некорректное значение x центра!");
		return;
	}
	yc = ystr.toInt(&correct);
	if (!correct)
	{
		QMessageBox::critical(this, "Ошибка",
							  "Некорректное значение y центра!");
		return;
	}
	r = rstr.toDouble(&correct);
	if (!correct || r <= 0)
	{
		QMessageBox::critical(this, "Ошибка",
							  "Некорректное значение радиуса!");
		return;
	}
	
	QPainter painter(&img);
	QPen pen(color);
	painter.setPen(pen);
	draw_circle(&painter, Point(xc, yc), r);
	
	scene.addPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_drawEllipseBtn_released()
{
	QString xstr = ui->xceEdit->text();
	QString ystr = ui->yceEdit->text();
	QString astr = ui->aEdit->text();
	QString bstr = ui->bEdit->text();
	
	bool correct = true;
	xc = xstr.toInt(&correct);
	if (!correct)
	{
		QMessageBox::critical(this, "Ошибка",
							  "Некорректное значение x центра!");
		return;
	}
	yc = ystr.toInt(&correct);
	if (!correct)
	{
		QMessageBox::critical(this, "Ошибка",
							  "Некорректное значение y центра!");
		return;
	}
	a = astr.toDouble(&correct);
	if (!correct || a <= 0)
	{
		QMessageBox::critical(this, "Ошибка",
							  "Некорректное значение длины полуоси a!");
		return;
	}
	b = bstr.toDouble(&correct);
	if (!correct || b <= 0)
	{
		QMessageBox::critical(this, "Ошибка",
							  "Некорректное значение длины полуоси b!");
		return;
	}
	
	QPainter painter(&img);
	QPen pen(color);
	painter.setPen(pen);
	draw_ellipse(&painter, Point(xc, yc), a, b);
	
	scene.addPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_drawConBtn_released()
{
	QString rstartstr = ui->rstartEdit->text();
	QString rstepstr = ui->rstepEdit->text();
	QString nstr = ui->nEdit->text();
	
	bool correct = true;
	r = rstartstr.toDouble(&correct);
	if (!correct || r <= 0)
	{
		QMessageBox::critical(this, "Ошибка",
							  "Некорректное начальное значение радиуса!");
		return;
	}
	dr = rstepstr.toDouble(&correct);
	if (!correct || dr <= 0)
	{
		QMessageBox::critical(this, "Ошибка",
							  "Некорректное значение шага изменения радиуса!");
		return;
	}
	n = nstr.toInt(&correct);
	if (!correct || n < 1)
	{
		QMessageBox::critical(this, "Ошибка",
							  "Некорректное значение количества окружностей!");
		return;
	}
	
	QPainter painter(&img);
	QPen pen(color);
	painter.setPen(pen);
	Point center(CANVAS_W / 2, CANVAS_W / 2);
	
	double rad = r;
	for (int i = 0; i < n; i++, rad += dr)
		draw_circle(&painter, center, rad);
	
	scene.addPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_drawConeEdit_released()
{
	QString astartstr = ui->astartEdit->text();
	QString bstartstr = ui->bstartEdit->text();
	QString astepstr = ui->astepEdit->text();
	QString nstr = ui->neEdit->text();
	
	bool correct = true;
	a = astartstr.toDouble(&correct);
	if (!correct || a <= 0)
	{
		QMessageBox::critical(this, "Ошибка",
							  "Некорректное начальное значение a!");
		return;
	}
	da = astepstr.toDouble(&correct);
	if (!correct || da <= 0)
	{
		QMessageBox::critical(this, "Ошибка",
							  "Некорректное значение шага изменения a!");
		return;
	}
	b = bstartstr.toDouble(&correct);
	if (!correct || b <= 0)
	{
		QMessageBox::critical(this, "Ошибка",
							  "Некорректное начальное значение b!");
		return;
	}
	n = nstr.toInt(&correct);
	if (!correct || n < 1)
	{
		QMessageBox::critical(this, "Ошибка",
							  "Некорректное значение количества окружностей!");
		return;
	}
	db = b * da / a;
	
	
	
	QPainter painter(&img);
	QPen pen(color);
	painter.setPen(pen);
	Point center(CANVAS_W / 2, CANVAS_W / 2);
	
	double alen = a, blen = b;
	for (int i = 0; i < n; i++, alen += da, blen += db)
		draw_ellipse(&painter, center, alen, blen);
	
	scene.addPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_circleAlgBox_currentIndexChanged(int index)
{
	switch (index)
	{
	case 0:
		draw_circle = draw_circle_canon;
		break;
	case 1:
		draw_circle = draw_circle_param;
		break;
	case 2:
		draw_circle = draw_circle_bresem;
		break;
	case 3:
		draw_circle = draw_circle_midpoint;
		break;
	default:
		draw_circle = draw_circle_lib;
	}
}

void MainWindow::on_ellipseAlgBox_currentIndexChanged(int index)
{
	switch (index)
	{
	case 0:
		draw_ellipse = draw_ellipse_canon;
		break;
	case 1:
		draw_ellipse = draw_ellipse_param;
		break;
	case 2:
		draw_ellipse = draw_ellipse_bresem;
		break;
	case 3:
		draw_ellipse = draw_ellipse_midpoint;
		break;
	default:
		draw_ellipse = draw_ellipse_lib;
	}
}
