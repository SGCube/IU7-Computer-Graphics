#include "window.h"
#include "ui_window.h"

window::window(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::window),
	house_obj(Point(START_X, START_Y))
{
	ui->setupUi(this);
	
	scene = new QGraphicsScene();
	scene->setSceneRect(0, 0, GVIEW_W, GVIEW_H);
	ui->gView->setScene(scene);
	
	house_obj.draw(ui->gView->scene());
}

window::~window()
{
	delete ui;
	delete scene;
}
