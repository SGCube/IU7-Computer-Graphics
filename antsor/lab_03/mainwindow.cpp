#include <QMessageBox>
#include <QPainter>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	pixmap(640, 640),
	color(255, 0, 0),
	scene(0, 0, 640, 640)
{
	ui->setupUi(this);
	ui->gView->setScene(&scene);
	
	pixmap.fill(QColor(255, 255, 255));
	scene.addPixmap(pixmap);
}

MainWindow::~MainWindow()
{
	delete ui;
}

/*void paintEvent(QPaintEvent *event)
{
	
}*/

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
	
	QPainter painter(&pixmap);
	QPen pen(color);
	
	painter.setPen(pen);
	painter.drawLine(x1, y1, x2, y2);
	
	scene.addPixmap(pixmap);
}

void MainWindow::on_bgcolBtn_released()
{
    color.setRgb(255, 255, 255);
}

void MainWindow::on_clearButton_released()
{
    scene.clear();
	pixmap.fill(QColor(255, 255, 255));
	scene.addPixmap(pixmap);
}
