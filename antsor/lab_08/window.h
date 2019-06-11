#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <vector>

#include "point.h"
#include "lineseg.hpp"
#include "polygon.h"

#include "canvas.h"

namespace Ui {
class Window;
}

class Window : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit Window(QWidget *parent = nullptr);
	~Window();
	
protected:
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	
private:
	Ui::Window *ui;
	
	QImage img;
	QImage imgNoClipper;
	Painter painter;
	
	std::vector<LineSeg> lineSegments;
	Polygon clipperPolygon;
	Point startPoint;
	
	bool drawClipper;
	
	QString coordText(Point& p);
	
signals:
	void ortDrawMode(bool isOrt);
	void isClipperToDraw(bool drawClipper);
	
public slots:
	void getStartPoint(Point p);
	void resetStartPoint();
	void getEndPoint(Point p);
	void getCurCoord(Point coord);
	
	void beginClipper(Point p);
	void addToClipper(Point p);
	void lockClipper();
	
private slots:
	void on_toLineRadio_clicked();
	void on_toClipperRadio_clicked();
	
	void on_clipButton_clicked();
	void on_clearButton_clicked();
	
	void on_palLineBtn_clicked();
	void on_palClipperBtn_clicked();
	void on_palClippedBtn_clicked();
};

#endif // WINDOW_H
