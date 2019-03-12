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
	
	if (dx != 0 || dy != 0)
	{
		house_obj.move(dx, dy);
		house_obj.draw(scene);
	}
}

void window::on_scaleButton_released()
{
    QString kxstr = ui->kxEdit->text();
	QString kystr = ui->kyEdit->text();
	QString xmstr = ui->xmEdit->text();
	QString ymstr = ui->ymEdit->text();
	
	bool correct = true;
	float kx, ky, xm, ym;
	kx = kxstr.toFloat(&correct);
	if (!correct)
	{
		QMessageBox::critical(this, "Ошибка",
							  "Некорректное значение kx!");
		return;
	}
	ky = kystr.toFloat(&correct);
	if (!correct)
	{
		QMessageBox::critical(this, "Ошибка",
							  "Некорректное значение ky!");
		return;
	}
	xm = xmstr.toFloat(&correct);
	if (!correct)
	{
		QMessageBox::critical(this, "Ошибка",
							  "Некорректное значение x центра!");
		return;
	}
	ym = ymstr.toFloat(&correct);
	if (!correct)
	{
		QMessageBox::critical(this, "Ошибка",
							  "Некорректное значение y центра!");
		return;
	}
	
	if (kx != 1 || ky != 1)
	{
		house_obj.scale(kx, ky, xm, ym);
		house_obj.draw(scene);
	}
}
