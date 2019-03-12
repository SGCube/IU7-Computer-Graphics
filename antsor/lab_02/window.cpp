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
	
	ui->undoButton->setDisabled(true);
	
	house_obj.draw(scene);
}

window::~window()
{
	delete ui;
	delete scene;
	comlist.clear();
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
	
	command_t com = {};
	set_move(&com, dx, dy);
	comlist.prepend(com);
	ui->undoButton->setDisabled(false);
	
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
	
	command_t com = {};
	set_scale(&com, kx, ky, Point(xm, ym));
	comlist.prepend(com);
	ui->undoButton->setDisabled(false);
	
	if (kx != 1 || ky != 1)
	{
		house_obj.scale(kx, ky, Point(xm, ym));
		house_obj.draw(scene);
	}
}

void window::on_rotateButton_released()
{
	QString degstr = ui->angleEdit->text();
	QString xcstr = ui->xmEdit->text();
	QString ycstr = ui->ymEdit->text();
	
	bool correct = true;
	int deg;
	float xc, yc;
	deg = degstr.toInt(&correct);
	if (!correct)
	{
		QMessageBox::critical(this, "Ошибка",
							  "Некорректное значение угла!");
		return;
	}
	xc = xcstr.toFloat(&correct);
	if (!correct)
	{
		QMessageBox::critical(this, "Ошибка",
							  "Некорректное значение x центра!");
		return;
	}
	yc = ycstr.toFloat(&correct);
	if (!correct)
	{
		QMessageBox::critical(this, "Ошибка",
							  "Некорректное значение y центра!");
		return;
	}
	
	command_t com = {};
	set_rotate(&com, deg, Point(xc, yc));
	comlist.prepend(com);
	ui->undoButton->setDisabled(false);
	
	if (deg != 0)
	{
		house_obj.rotate(deg, Point(xc, yc));
		house_obj.draw(scene);
	}
}

void window::on_undoButton_released()
{
    if (!comlist.isEmpty())
	{
		command_t com = comlist.takeFirst();
		
		if (com.type == MOVE_COM)
			house_obj.move(com.args.movarg.dx, com.args.movarg.dy);
		else if (com.type == SCALE_COM)
			house_obj.scale(com.args.sclarg.kx, com.args.sclarg.ky,
							com.args.sclarg.pm);
		else if (com.type == ROTATE_COM)
			house_obj.rotate(com.args.rotarg.deg, com.args.rotarg.pc);
		
		house_obj.draw(scene);
		
		if (comlist.isEmpty())
			ui->undoButton->setDisabled(true);
	}
}
