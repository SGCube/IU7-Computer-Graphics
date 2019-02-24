#include "draw.h"
#include <QGraphicsItem>

void drawTriangle(QGraphicsScene *scene, Triangle *tr)
{
	QPen pen = QPen(Qt::red, 1, Qt::SolidLine, Qt::FlatCap);
	
	QPoint ltcorn = tr->lt_corner();
	QPoint rbcorn = tr->rb_corner();
	
	float ww = rbcorn.x() - ltcorn.x();
	float wh = rbcorn.y() - ltcorn.y();
	float kw = scene->width() / ww;
	float kh = scene->height() / wh;
	float kdraw = (kw < kh) ? kw : kh;
	
	scene->addLine(tr->points[0].x(), tr->points[0].y(),
			tr->points[1].x(), tr->points[1].y(), pen);
	scene->addLine(tr->points[0].x(), tr->points[0].y(),
			tr->points[2].x(), tr->points[2].y(), pen);
	scene->addLine(tr->points[1].x(), tr->points[1].y(),
			tr->points[2].x(), tr->points[2].y(), pen);
	
	QPointF hv;
	QVector2D h = tr->getMinHeight(&hv);
	
	pen.setColor(Qt::blue);
	scene->addLine(hv.x(), hv.y(), hv.x() + h.x(), hv.y() + h.y(), pen);
}

void drawPoints(QGraphicsScene *scene, QPointF *plist, int n)
{
	QPen pen = QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap);
	QBrush brush = QBrush(QBrush(Qt::black, Qt::SolidPattern));
	QFont font = QFont("sans", 12);
	QString str;
	QGraphicsTextItem *label;
	
	for (int i = 0; i < n; i++)
	{
		scene->addEllipse(plist[i].x() - 2, plist[i].y() - 2, 4, 4, pen, brush);
		str = "№" + QString::number(i + 1);
		label = scene->addText(str, font);
		label->setX(plist[i].x() - label->boundingRect().width() / 2);
		label->setY(plist[i].y() - 2 - label->boundingRect().height());
		str = " (" + QString::number(plist[i].x()) + ", " +
				QString::number(plist[i].y()) + ")";
		label = scene->addText(str, font);
		label->setX(plist[i].x() - label->boundingRect().width() / 2);
		label->setY(plist[i].y() + 2);
		label->adjustSize();
	}
}

void draw(QGraphicsScene *scene, Triangle *tr, QPointF *plist, int n)
{
	scene->clear();
	QPoint ltcorn = tr->lt_corner();
	QPoint rbcorn = tr->rb_corner();
	drawTriangle(scene, tr);
	drawPoints(scene, plist, n);
}
