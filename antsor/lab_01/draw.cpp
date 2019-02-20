#include "draw.h"

void drawTriangle(QGraphicsScene *scene, Triangle *tr)
{
	QPen pen = QPen(Qt::red, 1, Qt::SolidLine, Qt::FlatCap);
	
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
	
	for (int i = 0; i < n; i++)
		scene->addEllipse(plist[i].x() - 2, plist[i].y() - 2, 4, 4, pen, brush);
}

void draw(QGraphicsScene *scene, Triangle *tr, QPointF *plist, int n)
{
	scene->clear();
	drawTriangle(scene, tr);
	drawPoints(scene, plist, n);
}
