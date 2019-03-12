#include <QMessageBox>

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
	
	house_obj.draw(scene);
}

window::~window()
{
	delete ui;
	delete scene;
}

void window::on_moveButton_released()
{
    QString dxstr = ui->dxEdit->text();
	QString dystr = ui->dyEdit->text();
	
	bool correct = true;
	int dx, dy;
	dx = dxstr.toInt(&correct);
	if (!correct)
	{
		QMessageBox::critical(this, "Ошибка", "Некорректное значение dx!");
		return;
	}
	dy = dystr.toInt(&correct);
	if (!correct)
	{
		QMessageBox::critical(this, "Ошибка", "Некорректное значение dy!");
		return;
	}
	
	house_obj.move(dx, dy);
	house_obj.draw(scene);
}
