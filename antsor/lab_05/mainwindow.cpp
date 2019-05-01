#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	scene(0, 0, 640, 640),
	img(640, 640, QImage::Format_RGB32),
	color_edge(0, 0, 0),
	color_fill(0, 0, 255),
	color_bg(255, 255, 255)
{
	ui->setupUi(this);
	ui->gView->setScene(&scene);
	
	QPixmap pxm(ui->colorEdge->rect().size());
	pxm.fill(color_edge);
	ui->colorEdge->setPixmap(pxm);
	pxm.fill(color_fill);
	ui->colorFill->setPixmap(pxm);
	pxm.fill(color_bg);
	ui->colorBg->setPixmap(pxm);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_palEdgeBtn_released()
{
	QColor newcolor = QColorDialog::getColor(color_edge, this);
	if (newcolor.isValid())
		color_edge = newcolor;
	QPixmap pxm(ui->colorEdge->rect().size());
	pxm.fill(color_edge);
	ui->colorEdge->setPixmap(pxm);
}

void MainWindow::on_palFillBtn_released()
{
	QColor newcolor = QColorDialog::getColor(color_fill, this);
	if (newcolor.isValid())
		color_fill = newcolor;
	QPixmap pxm(ui->colorFill->rect().size());
	pxm.fill(color_fill);
	ui->colorFill->setPixmap(pxm);
}

void MainWindow::on_palBgBtn_released()
{
	QColor newcolor = QColorDialog::getColor(color_bg, this);
	if (newcolor.isValid())
		color_bg = newcolor;
	QPixmap pxm(ui->colorBg->rect().size());
	pxm.fill(color_bg);
	ui->colorBg->setPixmap(pxm);
}
