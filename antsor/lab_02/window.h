#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include "house.h"

namespace Ui {
class window;
}

class window : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit window(QWidget *parent = 0);
	~window();
	
private:
	Ui::window *ui;
	QGraphicsScene *scene;
	House house_obj;
};

#endif // WINDOW_H
