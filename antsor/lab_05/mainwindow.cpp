#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWidget>
#include <QColorDialog>
#include <QMessageBox>

MainWindow::MainWindow(QImage *image, std::vector<Polygon> *polygons,
					   Painter *p, QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	painter(p),
	img(image),
	polygon_set(polygons),
	new_polygon(),
	color_edge(0, 0, 0),
	color_fill(0, 0, 255),
	color_bg(255, 255, 255)
{
	ui->setupUi(this);
	ui->gView->setMouseTracking(true);
	
	QPixmap pxm(ui->colorEdge->rect().size());
	pxm.fill(color_edge);
	ui->colorEdge->setPixmap(pxm);
	pxm.fill(color_fill);
	ui->colorFill->setPixmap(pxm);
	pxm.fill(color_bg);
	ui->colorBg->setPixmap(pxm);
	
	ui->lockButton->setDisabled(true);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::set_scene(QGraphicsScene *scene)
{
	ui->gView->setScene(scene);
}

void MainWindow::add_point(Point p)
{
	ui->pointTable->insertRow(ui->pointTable->rowCount());
	int row = ui->pointTable->rowCount() - 1;
	QTableWidgetItem *xitem = nullptr, *yitem = nullptr;
	xitem = new QTableWidgetItem(QString::number(p.x()));
	yitem = new QTableWidgetItem(QString::number(p.y()));
	ui->pointTable->setItem(row, 0, xitem);
	ui->pointTable->setItem(row, 1, yitem);
}

void MainWindow::end_polygon()
{
	ui->pointTable->insertRow(ui->pointTable->rowCount());
	int row = ui->pointTable->rowCount() - 1;
	QTableWidgetItem *xitem = nullptr, *yitem = nullptr;
	xitem = new QTableWidgetItem("=========");
	yitem = new QTableWidgetItem("=========");
	ui->pointTable->setItem(row, 0, xitem);
	ui->pointTable->setItem(row, 1, yitem);
}

void MainWindow::on_palEdgeBtn_released()
{
	QColor newcolor = QColorDialog::getColor(color_edge, this);
	if (newcolor.isValid())
		color_edge = newcolor;
	QPixmap pxm(ui->colorEdge->rect().size());
	pxm.fill(color_edge);
	ui->colorEdge->setPixmap(pxm);
	painter->set_color(color_edge);
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

void MainWindow::on_addButton_released()
{
	bool correct = true;
	QString xstr = ui->xEdit->text();
	QString ystr = ui->yEdit->text();
	int x = xstr.toInt(&correct);
	if (!correct)
	{
		QMessageBox::critical(this, "Ошибка", "Некорректное значение x!");
		return;
	}
	int y = ystr.toInt(&correct);
	if (!correct)
	{
		QMessageBox::critical(this, "Ошибка", "Некорректное значение y!");
		return;
	}
	ui->xEdit->clear();
	ui->yEdit->clear();
	
	Point new_point(x, y);
	add_point(new_point);
	
	painter->begin(img);
	painter->set_pen();
	
	if (new_polygon.number_of_vertexes() == 0)
		painter->drawPoint(x, y);
	else
	{
		Point plast = new_polygon.last_point();
		painter->drawLine(plast.x(), plast.y(), x, y);
	}
	QGraphicsScene *scene = ui->gView->scene();
	scene->addPixmap(QPixmap::fromImage(*img));
	
	painter->end();
	
	new_polygon.add_point(new_point);
	if (new_polygon.number_of_vertexes() > 2)
		ui->lockButton->setDisabled(false);
}

void MainWindow::on_lockButton_released()
{
    end_polygon();
	
	painter->begin(img);
	painter->set_pen();
	
	Point pfirst = new_polygon.first_point();
	Point plast = new_polygon.last_point();
	painter->drawLine(plast.x(), plast.y(), pfirst.x(), pfirst.y());
	
	QGraphicsScene *scene = ui->gView->scene();
	scene->addPixmap(QPixmap::fromImage(*img));
	
	painter->end();
	
	polygon_set->push_back(new_polygon);
	new_polygon.clear();
	
	ui->lockButton->setDisabled(true);
}
