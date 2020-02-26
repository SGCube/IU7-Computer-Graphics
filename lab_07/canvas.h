#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <vector>

#include "painter.h"
#include "point.h"

class Canvas : public QWidget
{
	Q_OBJECT
	
public:
	explicit Canvas(QWidget *parent = nullptr);
	void setCanvas(QImage* image, Painter* p);
	void setParLine(bool state);
	
protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	
private:
	QImage* img;
	Painter* painter;
	
	Point startPoint;
	bool ortDraw;
	bool isDrawing;
	bool isClipperToDraw;
	
signals:
	void startSegDraw(Point p);
	void breakSegDraw();
	void endSegDraw(Point p);
	void curCoord(Point p);
	
public slots:
	void setOrtDraw(bool state);
	void setDrawMode(bool isCutter);

};

#endif // CANVAS_H
