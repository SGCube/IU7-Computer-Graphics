#include <QDebug>

#include "canvas.h"

Canvas::Canvas(QWidget *parent) :
	QWidget(parent),
	img(nullptr),
	painter(nullptr),
	startPoint(0, 0),
	ortDraw(false),
	isDrawing(false),
	isClipperToDraw(false)
{
	setMouseTracking(true);
}

void Canvas::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);
	painter->begin(this);
	painter->drawImage(0, 0, *img);
	painter->end();
}

void Canvas::setCanvas(QImage *image, Painter *p)
{
	img = image;
	painter = p;
}

void Canvas::setParLine(bool state)
{
	ortDraw = state;
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::RightButton && isDrawing)
	{
		if (curPolygon.size() > 2)
		{
			isDrawing = false;
			painter->begin(img);
			lockPolygon();
			painter->end();
			emit endPolygonDraw();
			repaint();
		}
		return;
	}
	if (event->button() != Qt::LeftButton)
		return;
	
	int x = event->pos().x();
	int y = event->pos().y();
	
	if (startPoint == Point(x, y))
		return;
	
	if (isDrawing)
	{
		if (ortDraw)
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
		
		painter->begin(img);
		
		Point plast = curPolygon.last_point();
		if (isClipperToDraw)
			painter->drawClipper(plast.x(), plast.y(), x, y);
		else
			painter->drawLineSeg(plast.x(), plast.y(), x, y);
		addPointToPolygon(Point(x, y));
		emit drawingPolygon(Point(x, y));
		
		painter->end();
		repaint();
	}
	else
	{
		startPoint = Point(x, y);
		isDrawing = true;
		addPointToPolygon(startPoint);
		emit startPolygonDraw(startPoint);
	}
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
	int x = event->pos().x();
	int y = event->pos().y();
	
	emit curCoord(Point(x, y));
	
	if (!isDrawing)
		return;
	
	if (ortDraw)
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
	
	QImage tmpImg(*img);
	painter->begin(&tmpImg);
	Point plast = curPolygon.last_point();
	if (isClipperToDraw)
		painter->drawClipper(plast.x(), plast.y(), x, y);
	else
		painter->drawLineSeg(plast.x(), plast.y(), x, y);
	painter->end();
	
	QImage* tmpPtr = img;
	img = &tmpImg;
	repaint();
	img = tmpPtr;
}

void Canvas::addPointToPolygon(Point p)
{
	curPolygon.add_point(p);
}

void Canvas::lockPolygon()
{
	Point pfirst = curPolygon.first_point();
	Point plast = curPolygon.last_point();
	if (isClipperToDraw)
		painter->drawClipper(plast.x(), plast.y(), pfirst.x(), pfirst.y());
	else
		painter->drawLineSeg(plast.x(), plast.y(), pfirst.x(), pfirst.y());
	curPolygon.clear();
}

void Canvas::setOrtDraw(bool state)
{
	ortDraw = state;
}

void Canvas::setDrawMode(bool isCutter)
{
	isClipperToDraw = isCutter;
}
