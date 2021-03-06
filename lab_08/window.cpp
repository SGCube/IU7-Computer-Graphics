#include <QColorDialog>
#include <QMessageBox>

#include "window.h"
#include "ui_window.h"

#include "clipper.h"

Window::Window(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::Window),
	img(640, 640, QImage::Format_RGB32),
	imgNoClipper(img),
	painter(),
	startPoint(0, 0),
	drawClipper(false)
{
	ui->setupUi(this);
	ui->canvas->setCanvas(&img, &painter);
	img.fill(QColor(255, 255, 255));
	
	connect(ui->canvas, SIGNAL(curCoord(Point)),
			this, SLOT(getCurCoord(Point)));
	
	connect(ui->canvas, SIGNAL(startSegDraw(Point)),
			this, SLOT(getStartPoint(Point)));
	connect(ui->canvas, SIGNAL(breakSegDraw()),
			this, SLOT(resetStartPoint()));
	connect(ui->canvas, SIGNAL(endSegDraw(Point)),
			this, SLOT(getEndPoint(Point)));
	
	connect(ui->canvas, SIGNAL(startClipperDraw(Point)),
			this, SLOT(beginClipper(Point)));
	connect(ui->canvas, SIGNAL(clipperDraw(Point)),
			this, SLOT(addToClipper(Point)));
	connect(ui->canvas, SIGNAL(endClipperDraw()),
			this, SLOT(lockClipper()));
	
	
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

void Window::getStartPoint(Point p)
{
	startPoint = p;
	int row = ui->pointTable->rowCount();
	ui->pointTable->insertRow(row);
	QTableWidgetItem *item = new QTableWidgetItem(coordText(p));
	ui->pointTable->setItem(row, 0, item);
}

void Window::resetStartPoint()
{
	ui->pointTable->removeRow(ui->pointTable->rowCount() - 1);
}

void Window::getEndPoint(Point p)
{
	Point endPoint = p;
	lineSegments.push_back(LineSeg(startPoint, endPoint));
	
	int row = ui->pointTable->rowCount() - 1;
	QTableWidgetItem *item = new QTableWidgetItem(coordText(p));
	ui->pointTable->setItem(row, 1, item);
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

void Window::beginClipper(Point p)
{
	clipperPolygon.clear();
	int len = ui->clipperTable->rowCount();
	for (int i = 0; i < len; i++)
		ui->clipperTable->removeRow(0);
	
	addToClipper(p);
}

void Window::addToClipper(Point p)
{
	ui->clipperTable->insertRow(ui->clipperTable->rowCount());
	int row = ui->clipperTable->rowCount() - 1;
	QTableWidgetItem *xitem = nullptr, *yitem = nullptr;
	xitem = new QTableWidgetItem(QString::number(p.x()));
	yitem = new QTableWidgetItem(QString::number(p.y()));
	ui->clipperTable->setItem(row, 0, xitem);
	ui->clipperTable->setItem(row, 1, yitem);
	
	clipperPolygon.add_point(p);
}

void Window::lockClipper()
{
	
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
	if (clipperPolygon.number_of_vertexes() > 2)
	{
		Clipper clipper(clipperPolygon);
		
		painter.begin(&img);
		if (!clipper.clip(lineSegments, painter))
			QMessageBox::warning(this, "Ошибка", "Отсекатель не выпуклый!");
		painter.end();
		ui->canvas->repaint();
	}
}

void Window::on_clearButton_clicked()
{
	img.fill(QColor(255, 255, 255));
	ui->canvas->repaint();
	
	lineSegments.clear();
	int len = ui->pointTable->rowCount();
	for (int i = 0; i < len; i++)
		ui->pointTable->removeRow(0);
	
	clipperPolygon.clear();
	len = ui->clipperTable->rowCount();
	for (int i = 0; i < len; i++)
		ui->clipperTable->removeRow(0);
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
