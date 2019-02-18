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
    int rows = ui->pointTable->rowCount();	// количество точек (строк таблицы)
	
    /// проверка на достаточность
    
    if (rows < 3)
    {
        ui->msgFrame->setText(QString(
                                  "Недостаточно данных для решения задачи!"));
        return;
    }

    /// выделение памяти под точки
	
    QPointF *plist = new QPointF[rows];
    if (!plist)
    {
        ui->msgFrame->setText(QString(
                                  "Ошибка выделения памяти!"));
        return;
    }
	
    /// проверка на корректность содержимого таблицы
    
    bool correct = true;
	// строки для записи содержимого ячеек таблицы
    QString xstr, ystr;
	// номер точки
    int i = 0;
	// какая координата рассматривается (0 - X, 1 - Y)
    bool coord = 0;
	// координаты текущей точки
	float x, y;
	
    for(i = 0; i < rows && correct; i++)
    {
        xstr = ui->pointTable->item(i, 0)->text();
        ystr = ui->pointTable->item(i, 1)->text();
        coord = 0;
        x = xstr.toFloat(&correct);
        if (correct)
        {
            y = ystr.toFloat(&correct);
            coord = 1;
			if (correct)
			{
				plist[i].setX(x);
				plist[i].setY(y);
			}
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
		delete [] plist;
		return;
    }
	
	/// решение задачи
	Triangle tr;	// треугольник решения
	QVector2D h;	// наименьшая высота
	QPointF hvertex;	// вершина наименьшей высоты
	
	/// вывод решения в статусное окно
	if (solve(plist, ui->pointTable->rowCount(), &tr, &h, &hvertex))
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
		msg.append(QString::number(h.length()));
		msg.append(", вершина: (");
		msg.append(QString::number(hvertex.x()));
		msg.append(", ");
		msg.append(QString::number(hvertex.y()));
		msg.append(") ");
		ui->msgFrame->setText(QString(msg));
	}
	
    delete [] plist;
}
