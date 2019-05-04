#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fill.h"

#include <QWidget>
#include <QColorDialog>
#include <QMessageBox>

MainWindow::MainWindow(QImage *image, std::vector<Polygon> *polygons,
					   Polygon *pl, Painter *p, QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	painter(p),
	img(image),
	polygon_set(polygons),
	new_polygon(pl),
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
	xitem = new QTableWidgetItem("=======");
	yitem = new QTableWidgetItem("=======");
	ui->pointTable->setItem(row, 0, xitem);
	ui->pointTable->setItem(row, 1, yitem);
}

void MainWindow::lock_disable(bool d)
{
	ui->lockButton->setDisabled(d);
}

void MainWindow::on_palEdgeBtn_released()
{
	QColor newcolor = QColorDialog::getColor(color_edge, this);
	if (newcolor.isValid())
		color_edge = newcolor;
	QPixmap pxm(ui->colorEdge->rect().size());
	pxm.fill(color_edge);
	ui->colorEdge->setPixmap(pxm);
	painter->set_color_edge(color_edge);
}

void MainWindow::on_palFillBtn_released()
{
	QColor newcolor = QColorDialog::getColor(color_fill, this);
	if (newcolor.isValid())
		color_fill = newcolor;
	QPixmap pxm(ui->colorFill->rect().size());
	pxm.fill(color_fill);
	ui->colorFill->setPixmap(pxm);
	painter->set_color_fill(color_fill);
}

void MainWindow::on_palBgBtn_released()
{
	QColor newcolor = QColorDialog::getColor(color_bg, this);
	if (newcolor.isValid())
		color_bg = newcolor;
	QPixmap pxm(ui->colorBg->rect().size());
	pxm.fill(color_bg);
	ui->colorBg->setPixmap(pxm);
	painter->set_color_bg(color_bg);
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
	painter->set_edge();
	
	if (new_polygon->number_of_vertexes() == 0)
		painter->drawPoint(x, y);
	else
	{
		Point plast = new_polygon->last_point();
		painter->drawLine(plast.x(), plast.y(), x, y);
	}
	QGraphicsScene *scene = ui->gView->scene();
	scene->addPixmap(QPixmap::fromImage(*img));
	
	painter->end();
	
	new_polygon->add_point(new_point);
	if (new_polygon->number_of_vertexes() > 2)
		ui->lockButton->setDisabled(false);
}

void MainWindow::on_lockButton_released()
{
	if (new_polygon->number_of_vertexes() < 3)
	{
		ui->lockButton->setDisabled(false);
		return;
	}
	
    end_polygon();
	
	painter->begin(img);
	painter->set_edge();
	
	Point pfirst = new_polygon->first_point();
	Point plast = new_polygon->last_point();
	painter->drawLine(plast.x(), plast.y(), pfirst.x(), pfirst.y());
	
	QGraphicsScene *scene = ui->gView->scene();
	scene->addPixmap(QPixmap::fromImage(*img));
	
	painter->end();
	
	polygon_set->push_back(*new_polygon);
	new_polygon->clear();
	
	ui->lockButton->setDisabled(true);
}

void MainWindow::on_clearButton_released()
{
    img->fill(color_bg);
	QGraphicsScene *scene = ui->gView->scene();
	scene->addPixmap(QPixmap::fromImage(*img));
	polygon_set->clear();
	new_polygon->clear();
	ui->lockButton->setDisabled(true);
	
	int len = ui->pointTable->rowCount();
	for (int i = 0; i < len; i++)
		ui->pointTable->removeRow(0);
}

void MainWindow::on_fillButton_released()
{
	ui->addButton->setDisabled(true);
	ui->lockButton->setDisabled(true);
	ui->clearButton->setDisabled(true);
	ui->fillButton->setDisabled(true);
	ui->xEdit->setDisabled(true);
	ui->yEdit->setDisabled(true);
	ui->palBgBtn->setDisabled(true);
	ui->palEdgeBtn->setDisabled(true);
	ui->palFillBtn->setDisabled(true);
	ui->delayCheck->setDisabled(true);
	ui->delaySpinBox->setDisabled(true);
	
	bool correct = true;
	QString xstr = ui->xsEdit->text();
	QString ystr = ui->ysEdit->text();
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
	Point seed(x, y);
	
	int delay = (ui->delayCheck->isChecked()) ? ui->delaySpinBox->value() : 0;
	
	fill(img, ColorSet(color_edge, color_fill, color_bg),
		 ui->gView->scene(), seed, delay);
	
	ui->addButton->setDisabled(false);
	ui->lockButton->setDisabled(false);
	ui->clearButton->setDisabled(false);
	ui->fillButton->setDisabled(false);
	ui->xEdit->setDisabled(false);
	ui->yEdit->setDisabled(false);
	ui->palBgBtn->setDisabled(false);
	ui->palEdgeBtn->setDisabled(false);
	ui->palFillBtn->setDisabled(false);
	ui->delayCheck->setDisabled(false);
	ui->delaySpinBox->setDisabled(false);
}
