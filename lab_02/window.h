#ifndef WINDOW_H
#define WINDOW_H

#define GVIEW_X 20
#define GVIEW_Y 20
#define GVIEW_W 600
#define GVIEW_H 600

#include <QMainWindow>
#include "house.h"
#include "command.h"

namespace Ui {
class window;
}

class window : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit window(QWidget *parent = 0);
	~window();
	
private slots:
	void on_moveButton_released();
	
	void on_scaleButton_released();
	
	void on_rotateButton_released();
	
	void on_undoButton_released();
	
private:
	Ui::window *ui;
	QGraphicsScene *scene;
	House house_obj;
	QList<command_t> comlist;
};

#endif // WINDOW_H
