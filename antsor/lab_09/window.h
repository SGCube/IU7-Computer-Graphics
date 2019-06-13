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
	
	std::vector<Polygon> polygons;
	Polygon clipperPolygon;
	Polygon drawingPolygon;
	bool drawClipper;
	
	QString coordText(Point& p);
	
	void clearPolygons();
	void clearClipper();
	
signals:
	void ortDrawMode(bool isOrt);
	void isClipperToDraw(bool drawClipper);
	
public slots:
	void getCurCoord(Point coord);
	
	void beginPolygon(Point p);
	void addToPolygon(Point p);
	void lockPolygon();
	
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
