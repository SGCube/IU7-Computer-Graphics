#ifndef PAINTERWIDGET_H
#define PAINTERWIDGET_H

#include <QWidget>
#include <QPainter>

#include "triangle.h"

class PainterWidget : public QWidget
{
	Q_OBJECT
public:
	explicit PainterWidget(QWidget *parent = nullptr);
	~PainterWidget();
	
	void drawTriangle(Triangle *tr);
	void drawPoints(QPointF *plist, int n);
	
protected:
	void paintEvent(QPaintEvent *event);
};

#endif // PAINTERWIDGET_H
