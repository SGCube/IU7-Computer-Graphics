#include <QDebug>

#include "canvas.h"

Canvas::Canvas(QImage& image, Painter& p, QWidget *parent) :
	QWidget(parent),
	img(image),
	painter(p),
	startPoint(0, 0),
	parLine(false),
	isSegDrawing(false)
{
	setMouseTracking(true);
}

void Canvas::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);
	painter.begin(this);
	painter.drawImage(0, 0, img);
	painter.end();
}

void Canvas::set_parline(bool state)
{
	parLine = state;
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::RightButton)
	{
		emit breakSegDraw();
		return;
	}
	if (event->button() != Qt::LeftButton)
		return;
	
	int x = event->pos().x();
	int y = event->pos().y();
	
	if (isSegDrawing)
	{
		if (parLine)
		{
			int xx = x - startPoint.x(), yy = startPoint.y() - y;
			if (yy > xx)
			{
				if (yy > -xx)
					x = startPoint.x();
				else
					y = startPoint.y();
			}
			else
			{
				if (yy > -xx)
					y = startPoint.y();
				else
					x = startPoint.x();
			}
		}
		
		painter.begin(&img);
		painter.set_edge();
		painter.drawLine(startPoint.x(), startPoint.y(), x, y);
		painter.end();
		
		isSegDrawing = false;
		emit endSegDraw(Point(x, y));
	}
	else
	{
		startPoint = Point(x, y);
		isSegDrawing = true;
		emit startSegDraw(startPoint);
	}
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
	int x = event->pos().x();
	int y = event->pos().y();
	
	emit curCoord(Point(x, y));
	
	if (!isSegDrawing)
		return;
	
	if (parLine)
	{
		int xx = x - startPoint.x(), yy = startPoint.y() - y;
		if (yy > xx)
		{
			if (yy > -xx)
				x = startPoint.x();
			else
				y = startPoint.y();
		}
		else
		{
			if (yy > -xx)
				y = startPoint.y();
			else
				x = startPoint.x();
		}
	}
	
	QImage tmpImg(img);
	painter.begin(&tmpImg);
	painter.set_edge();
	painter.drawLine(startPoint.x(), startPoint.y(), x, y);
	painter.end();
	
	QImage imgSaved = img;
	img = tmpImg;
	repaint();
	img = imgSaved;
}
