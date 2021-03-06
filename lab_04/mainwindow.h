#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

#include "point.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	
/*protected:
	void paintEvent(QPaintEvent *);*/
	
private slots:
	
	void on_bgcolBtn_released();
	
	void on_clearButton_released();
	
	void on_palletteBtn_released();
	
	void on_redBtn_released();
	
	void on_blueBtn_released();
	
	void on_greenBtn_released();
	
	void on_blackBtn_released();
	
	void on_centerBtn_released();
	
	void on_centereBtn_released();
	
	void on_drawCircleBtn_released();
	
	void on_drawEllipseBtn_released();
	
	void on_drawConBtn_released();
	
	void on_drawConeEdit_released();
	
	void on_circleAlgBox_currentIndexChanged(int index);
	
	void on_ellipseAlgBox_currentIndexChanged(int index);
	
private:
	Ui::MainWindow *ui;
	QGraphicsScene scene;
	QImage img;
	QColor color;
	
	void set_colorFrame();
	
	int xc, yc;
	double r, a, b;
	double dr, da, db;
	int n;
	
	void (*draw_circle)(QPainter *, Point, double);
	void (*draw_ellipse)(QPainter *, Point, double, double);
};

#endif // MAINWINDOW_H
