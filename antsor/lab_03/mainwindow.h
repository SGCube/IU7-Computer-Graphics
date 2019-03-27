#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

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
	void on_drawLineBtn_released();
	
	void on_bgcolBtn_released();
	
	void on_clearButton_released();
	
	void on_palletteBtn_released();
	
private:
	Ui::MainWindow *ui;
	QGraphicsScene scene;
	QImage img;
	QColor color;
	
	double x1, y1, x2, y2;
	
	void set_colorFrame();
};

#endif // MAINWINDOW_H
