#include "window.h"
#include "ui_window.h"

window::window(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::window),
	house_obj(START_X, START_Y)
{
	ui->setupUi(this);
}

window::~window()
{
	delete ui;
}
