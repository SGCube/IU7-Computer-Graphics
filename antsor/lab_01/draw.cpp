#include "draw.h"
#include <QGraphicsItem>
#include <cmath>

void drawTriangle(QGraphicsScene *scene, Triangle *tr, float k,
				  QPoint center)
{
	// координаты концов отрезков
	int x1, y1, x2, y2;
	// центр масштабирования
	QPoint pm = QPoint(VIEW_W / 2, - VIEW_H / 2);
	// определение смещения центра
	int dx = pm.x() - center.x();
	int dy = pm.y() - center.y();
	
	// рисование треугольника
	QPen pen = QPen(Qt::red, 1, Qt::SolidLine, Qt::FlatCap);
	
	for (int i = 0; i < 3; i++)
	{
		// определение координат на рисунке
		x1 = round(k * (tr->points[i % 3].x() + dx) + (1 - k) * pm.x());
		y1 = -round(k * (tr->points[i % 3].y() + dy) + (1 - k) * pm.y());
		x2 = round(k * (tr->points[(i + 1) % 3].x() + dx) + (1 - k) * pm.x());
		y2 = -round(k * (tr->points[(i + 1) % 3].y() + dy) + (1 - k) * pm.y());
		
		scene->addLine(x1, y1, x2, y2, pen);
	}
	
	// рисование высоты
	pen.setColor(Qt::blue);
	QPointF hv;
	QVector2D h = tr->getMinHeight(&hv);
	
	x1 = round(k * (hv.x() + dx) + (1 - k) * pm.x());
	y1 = -round(k * (hv.y() + dy) + (1 - k) * pm.y());
	x2 = round(k * (hv.x() + h.x() + dx) + (1 - k) * pm.x());
	y2 = -round(k * (hv.y() + h.y() + dy) + (1 - k) * pm.y());
	
	scene->addLine(x1, y1, x2, y2, pen);
}

void drawPoints(QGraphicsScene *scene, QPointF *plist, int n, float k,
				QPoint center)
{
	QPen pen = QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap);
	QBrush brush = QBrush(QBrush(Qt::black, Qt::SolidPattern));
	QFont font = QFont("sans", 12);
	
	QString str;
	QGraphicsTextItem *label;
	
	float x, y;
	
	for (int i = 0; i < n; i++)
	{
		//рисование точки
		scene->addEllipse(plist[i].x() - 2, plist[i].y() - 2, 4, 4, pen, brush);
		
		// подпись точки
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
	
	// определение крайних координат "картины"
	QPoint ltcorn = tr->lt_corner();
	QPoint rbcorn = tr->rb_corner();
	
	// определение коэффициента масштабирования
	float ww = rbcorn.x() - ltcorn.x();
	float wh = rbcorn.y() - ltcorn.y();
	float kw = (VIEW_W - PAD_X * 2) / ww;
	float kh = (VIEW_H - PAD_Y * 2) / wh;
	float kdraw = (kw < kh) ? kw : kh;
	
	// центр "картины"
	QPoint center = QPoint(round(ltcorn.x() + ww / 2),
						   round(ltcorn.y() + wh / 2));
	
	drawTriangle(scene, tr, kdraw, center);
	//drawPoints(scene, plist, n, kdraw, center);
}
