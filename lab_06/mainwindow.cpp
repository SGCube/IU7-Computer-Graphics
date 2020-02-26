#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fill.h"

#include <QWidget>
#include <QColorDialog>
#include <QMessageBox>
#include <QLayout>
#include <canvas.h>

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
	ui->canvas->canvas_set(image, polygons, pl, p);
	
	connect(ui->canvas, SIGNAL(addPoint(Point)), this, SLOT(add_point(Point)));
	connect(ui->canvas, SIGNAL(curCoord(Point)), this, SLOT(cur_coord(Point)));
	connect(ui->canvas, SIGNAL(lockPolygon()), this, SLOT(lock_polygon()));
	connect(ui->canvas, SIGNAL(setSpan(Point)), this, SLOT(set_span(Point)));
	
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

void MainWindow::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Shift)
		ui->canvas->set_parline(true);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Shift)
		ui->canvas->set_parline(false);
}

void MainWindow::set_span(Point p)
{
	ui->xsEdit->setValue(p.x());
	ui->ysEdit->setValue(p.y());
}

void MainWindow::cur_coord(Point p)
{
	QString str = "Текущие координаты:\n(";
	str.append(QString::number(p.x()));
	str.append(", ");
	str.append(QString::number(p.y()));
	str.append(")");
	ui->coord->setText(str);
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
	
	if (new_polygon->number_of_vertexes() > 2)
		lock_disable(false);
}

void MainWindow::lock_polygon()
{
	ui->pointTable->insertRow(ui->pointTable->rowCount());
	int row = ui->pointTable->rowCount() - 1;
	QTableWidgetItem *xitem = nullptr, *yitem = nullptr;
	xitem = new QTableWidgetItem("=======");
	yitem = new QTableWidgetItem("=======");
	ui->pointTable->setItem(row, 0, xitem);
	ui->pointTable->setItem(row, 1, yitem);
	
	lock_disable(true);
}

void MainWindow::lock_disable(bool d)
{
	ui->lockButton->setDisabled(d);
}

void MainWindow::buttons_setDisabled(bool d)
{
	ui->addButton->setDisabled(d);
	ui->lockButton->setDisabled(d);
	ui->clearButton->setDisabled(d);
	ui->fillButton->setDisabled(d);
	ui->xEdit->setDisabled(d);
	ui->yEdit->setDisabled(d);
	ui->palBgBtn->setDisabled(d);
	ui->palEdgeBtn->setDisabled(d);
	ui->palFillBtn->setDisabled(d);
	ui->delaySpinBox->setDisabled(d);
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
	int x = ui->xEdit->value();
	int y = ui->yEdit->value();
	ui->xEdit->clear();
	ui->yEdit->clear();
	
	Point new_point(x, y);
	add_point(new_point);
	ui->canvas->add_point(new_point);
}

void MainWindow::on_lockButton_released()
{
    lock_polygon();
	ui->canvas->lock_polygon();
}

void MainWindow::on_clearButton_released()
{
    img->fill(color_bg);
	ui->canvas->repaint();
	
	polygon_set->clear();
	new_polygon->clear();
	ui->lockButton->setDisabled(true);
	
	int len = ui->pointTable->rowCount();
	for (int i = 0; i < len; i++)
		ui->pointTable->removeRow(0);
}

void MainWindow::on_fillButton_released()
{
	buttons_setDisabled(true);
	
	int xs = ui->xsEdit->value();
	int ys = ui->ysEdit->value();
	
	Point span(xs, ys);
	fill(img, ColorSet(color_edge, color_fill, color_bg),
		 ui->canvas, span, ui->delaySpinBox->value());
	
	buttons_setDisabled(false);
}
