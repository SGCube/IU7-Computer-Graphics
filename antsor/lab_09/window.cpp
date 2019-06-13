#include <QColorDialog>

#include "window.h"
#include "ui_window.h"

#include "clipper.h"

Window::Window(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::Window),
	img(640, 640, QImage::Format_RGB32),
	imgNoClipper(img),
	painter(),
	drawClipper(false)
{
	ui->setupUi(this);
	ui->canvas->setCanvas(&img, &painter);
	img.fill(QColor(255, 255, 255));
	
	connect(ui->canvas, SIGNAL(curCoord(Point)),
			this, SLOT(getCurCoord(Point)));
	
	connect(ui->canvas, SIGNAL(startPolygonDraw(Point)),
			this, SLOT(beginPolygon(Point)));
	connect(ui->canvas, SIGNAL(drawingPolygon(Point)),
			this, SLOT(addToPolygon(Point)));
	connect(ui->canvas, SIGNAL(endPolygonDraw()),
			this, SLOT(lockPolygon()));
	
	
	connect(this, SIGNAL(ortDrawMode(bool)), ui->canvas, SLOT(setOrtDraw(bool)));
	connect(this, SIGNAL(isClipperToDraw(bool)), ui->canvas, SLOT(setDrawMode(bool)));
	
	QPixmap pxm(ui->colorLine->rect().size());
	pxm.fill(painter.getColorLine());
	ui->colorLine->setPixmap(pxm);
	pxm.fill(painter.getColorClipper());
	ui->colorClipper->setPixmap(pxm);
	pxm.fill(painter.getColorClipped());
	ui->colorClipped->setPixmap(pxm);
}

Window::~Window()
{
	delete ui;
}

void Window::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Shift)
		ortDrawMode(true);
}

void Window::keyReleaseEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Shift)
		ortDrawMode(false);
}

QString Window::coordText(Point &p)
{
	QString str = "(";
	str.append(QString::number(p.x()));
	str.append(", ");
	str.append(QString::number(p.y()));
	str.append(")");
	return str;
}

void Window::clearPolygons()
{
	polygons.clear();
	int len = ui->polygonTable->rowCount();
	for (int i = 0; i < len; i++)
		ui->polygonTable->removeRow(0);
}

void Window::clearClipper()
{
	clipperPolygon.clear();
	int len = ui->clipperTable->rowCount();
	for (int i = 0; i < len; i++)
		ui->clipperTable->removeRow(0);
}

void Window::getCurCoord(Point coord)
{
	QString str = "Текущие координаты: (";
	str.append(QString::number(coord.x()));
	str.append(", ");
	str.append(QString::number(coord.y()));
	str.append(")");
	ui->coord->setText(str);
}

void Window::beginPolygon(Point p)
{
	if (drawClipper)
		clearClipper();
	addToPolygon(p);
}

void Window::addToPolygon(Point p)
{
	QTableWidget* table = ui->polygonTable;
	if (drawClipper)
		table = ui->clipperTable;
	
	table->insertRow(table->rowCount());
	int row = table->rowCount() - 1;
	QTableWidgetItem *xitem = nullptr, *yitem = nullptr;
	xitem = new QTableWidgetItem(QString::number(p.x()));
	yitem = new QTableWidgetItem(QString::number(p.y()));
	table->setItem(row, 0, xitem);
	table->setItem(row, 1, yitem);
	
	drawingPolygon.add_point(p);
}

void Window::lockPolygon()
{
	if (drawClipper)
		clipperPolygon = drawingPolygon;
	else
	{
		ui->polygonTable->insertRow(ui->polygonTable->rowCount());
		int row = ui->polygonTable->rowCount() - 1;
		QTableWidgetItem *xitem = nullptr, *yitem = nullptr;
		xitem = new QTableWidgetItem("===");
		yitem = new QTableWidgetItem("===");
		ui->polygonTable->setItem(row, 0, xitem);
		ui->polygonTable->setItem(row, 1, yitem);
		
		polygons.push_back(drawingPolygon);
	}
	drawingPolygon.clear();
}

void Window::on_toLineRadio_clicked()
{
    drawClipper = false;
	ui->toClipperRadio->setChecked(false);
	emit isClipperToDraw(drawClipper);
}

void Window::on_toClipperRadio_clicked()
{
	drawClipper = true;
	ui->toLineRadio->setChecked(false);
	emit isClipperToDraw(drawClipper);
}

void Window::on_clipButton_clicked()
{
	if (clipperPolygon.size() > 0)
	{
		Clipper clipper(clipperPolygon);
		
		painter.begin(&img);
		clipper.clip(polygons, painter);
		painter.end();
		ui->canvas->repaint();
	}
}

void Window::on_clearButton_clicked()
{
	img.fill(QColor(255, 255, 255));
	ui->canvas->repaint();
	
	drawingPolygon.clear();
	clearPolygons();
	clearClipper();
}

void Window::on_palLineBtn_clicked()
{
	QColor oldcolor = painter.getColorLine();
	QColor newcolor = QColorDialog::getColor(oldcolor, this);
	if (newcolor.isValid())
	{
		QPixmap pxm(ui->colorLine->rect().size());
		pxm.fill(newcolor);
		ui->colorLine->setPixmap(pxm);
		painter.setColorLine(newcolor);
	}
}

void Window::on_palClipperBtn_clicked()
{
	QColor oldcolor = painter.getColorClipper();
	QColor newcolor = QColorDialog::getColor(oldcolor, this);
	if (newcolor.isValid())
	{
		QPixmap pxm(ui->colorClipper->rect().size());
		pxm.fill(newcolor);
		ui->colorClipper->setPixmap(pxm);
		painter.setColorClipper(newcolor);
	}
}

void Window::on_palClippedBtn_clicked()
{
	QColor oldcolor = painter.getColorClipped();
	QColor newcolor = QColorDialog::getColor(oldcolor, this);
	if (newcolor.isValid())
	{
		QPixmap pxm(ui->colorClipped->rect().size());
		pxm.fill(newcolor);
		ui->colorClipped->setPixmap(pxm);
		painter.setColorClipped(newcolor);
	}
}
