#include "painterwidget.h"

PainterWidget::PainterWidget(QWidget *parent) : QWidget(parent)
{
}

PainterWidget::~PainterWidget()
{
}

void PainterWidget::drawTriangle(Triangle *tr)
{
	QPainter painter(this);
	
	painter.begin(this);
	painter.setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::FlatCap));
	painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
	
	painter.drawLine(tr->points[0], tr->points[1]);
	painter.drawLine(tr->points[1], tr->points[2]);
	painter.drawLine(tr->points[2], tr->points[0]);
	painter.end();
}

void PainterWidget::drawPoints(QPointF *plist, int n)
{
	QPainter painter(this);
	
	painter.begin(this);
	painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
	painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
	
	for (int i = 0; i < n; i++)
		painter.drawPoint(plist[i]);
	update();
	painter.end();
}

void PainterWidget::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);
	QPainter painter(this);
	
	painter.setBackground(QBrush(Qt::white, Qt::SolidPattern));
	painter.setBackgroundMode(Qt::OpaqueMode);
	/*painter.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
	
	painter.drawEllipse(100, 50, 150, 150);*/
}
