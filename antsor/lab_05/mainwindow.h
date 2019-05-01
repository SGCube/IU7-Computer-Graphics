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
	
private slots:
	void on_palEdgeBtn_released();
	
	void on_palFillBtn_released();
	
	void on_palBgBtn_released();
	
private:
	Ui::MainWindow *ui;
	QGraphicsScene scene;
	QImage img;
	QColor color_edge;
	QColor color_fill;
	QColor color_bg;
};

#endif // MAINWINDOW_H
