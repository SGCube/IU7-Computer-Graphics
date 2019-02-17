#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "triangle.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addButton_released()
{
    ui->pointTable->insertRow(ui->pointTable->rowCount());
}

void MainWindow::on_delAllButton_released()
{
    for (int k = ui->pointTable->rowCount(); k > 0; k--)
        ui->pointTable->removeRow(ui->pointTable->rowCount() - 1);
}

void MainWindow::on_delButton_released()
{
    ui->pointTable->removeRow(ui->pointTable->currentRow());
}

void MainWindow::on_drawButton_released()
{
    /// подготовка данных
    ///
    int rows = ui->pointTable->rowCount();
    /// проверка на достаточность
    if (rows < 3)
    {
        ui->msgFrame->setText(QString(
                                  "Недостаточно данных для решения задачи!"));
        return;
    }

    /// выделение памяти под точки
    float **plist = new float * [rows];
    if (!plist)
    {
        ui->msgFrame->setText(QString(
                                  "Ошибка выделения памяти!"));
        return;
    }
    for(int i = 0; i < rows; i++)
    {
        plist[i] = new float [2];
        if (!plist[i])
        {
            ui->msgFrame->setText(QString(
                                      "Ошибка выделения памяти!"));
            for(int j = 0; j < i; j++)
                delete [] plist[j];
            delete [] plist;
            return;
        }
    }

    /// проверка на корректность
    bool correct = true;
    QString xstr, ystr;
    int i = 0;
    bool coord = 0;
    for(i = 0; i < rows && correct; i++)
    {
        xstr = ui->pointTable->item(i, 0)->text();
        ystr = ui->pointTable->item(i, 1)->text();
        coord = 0;
        plist[i][0] = xstr.toFloat(&correct);
        if (correct)
        {
            plist[i][1] = ystr.toFloat(&correct);
            coord = 1;
        }
    }
    if (!correct)
    {
        QString msg("Некорректные данные: точка №");
        msg.append(QString::number(i));
        msg.append(", координата ");
        if (coord == 0)
            msg.append("X!");
        else
            msg.append("Y!");
        ui->msgFrame->setText(QString(msg));
    }
	else
	{
		float hmin = -1;
		Triangle tr = solve(plist, ui->pointTable->rowCount(), &hmin);
		if (hmin == -1)
		{
			QString msg("Невозможно построить треугольник!");
			ui->msgFrame->setText(QString(msg));
		}
		else
		{
			QString msg("Треугольник:\nВершины: ");
			for (int i = 0; i < 3; i++)
			{
				msg.append("(");
				msg.append(QString::number(tr.points[i].x()));
				msg.append(", ");
				msg.append(QString::number(tr.points[i].y()));
				msg.append(") ");
			}
			msg.append("\nНаименьшая высота: ");
			msg.append(QString::number(hmin));
			ui->msgFrame->setText(QString(msg));
		}
	}
	
	
    for(int i = 0; i < rows && correct; i++)
        delete [] plist[i];
    delete [] plist;
}
