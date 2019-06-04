#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::Window),
	img(640, 640, QImage::Format_RGB32),
	painter(),
	startPoint(0, 0),
	colorLine(0, 0, 0),
	colorCutter(0, 0, 255),
	colorCutted(255, 0, 0),
	drawCutter(false)
{
	ui->setupUi(this);
	ui->canvas->setCanvas(&img, &painter);
	img.fill(QColor(255, 255, 255));
	
	connect(ui->canvas, SIGNAL(startSegDraw(Point)),
			this, SLOT(getStartPoint(Point)));
	connect(ui->canvas, SIGNAL(breakSegDraw()),
			this, SLOT(resetStartPoint()));
	connect(ui->canvas, SIGNAL(endSegDraw(Point)),
			this, SLOT(getEndPoint(Point)));
	connect(ui->canvas, SIGNAL(curCoord(Point)),
			this, SLOT(getCurCoord(Point)));
	
	connect(this, SIGNAL(ortDrawMode(bool)), ui->canvas, SLOT(setOrtDraw(bool)));
	connect(this, SIGNAL(isCutterToDraw(bool)), ui->canvas, SLOT(setDrawMode(bool)));
	
	QPixmap pxm(ui->colorLine->rect().size());
	pxm.fill(colorLine);
	ui->colorLine->setPixmap(pxm);
	pxm.fill(colorCutter);
	ui->colorCutter->setPixmap(pxm);
	pxm.fill(colorCutted);
	ui->colorCutted->setPixmap(pxm);
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
	QString str = "Текущие\nкоординаты:\n(";
	str.append(QString::number(coord.x()));
	str.append(", ");
	str.append(QString::number(coord.y()));
	str.append(")");
	ui->coord->setText(str);
}

void Window::on_toLineRadio_clicked()
{
    drawCutter = false;
	ui->toCutterRadio->setChecked(false);
	emit isCutterToDraw(drawCutter);
}

void Window::on_toCutterRadio_clicked()
{
	drawCutter = true;
	ui->toLineRadio->setChecked(false);
	emit isCutterToDraw(drawCutter);
}
