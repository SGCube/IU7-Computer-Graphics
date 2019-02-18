#include <QTableWidget>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "plist.h"
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
	QPointF *plist = NULL;					// список точек
	
    /// проверка на достаточность
    if (rows < 3)
    {
        ui->msgFrame->setText(QString(
                                  "Недостаточно данных для решения задачи!"));
        return;
    }
	
	/// получение списка точек
	int no = -1;		// номер некорректной точки
	bool coord = 0;		// некорректная координата (0 - X, 1 - Y)
	int rc = get_plist(ui->pointTable, &plist, rows, &no, &coord);
	
	if (rc == ERR_PLIST_MEM)
	{
        ui->msgFrame->setText(QString("Ошибка выделения памяти!"));
		return;
	}
	if (rc == ERR_PLIST_VAL)
    {
        QString msg("Некорректные данные: точка №");
        msg.append(QString::number(no));
        msg.append(", координата ");
        if (coord == 0)
            msg.append("X!");
        else
            msg.append("Y!");
        ui->msgFrame->setText(QString(msg));
		return;
    }
	
	/// решение задачи
	Triangle tr;	// треугольник решения
	QVector2D h;	// наименьшая высота
	QPointF hvertex;	// вершина наименьшей высоты
	
	if (!solve(plist, rows, &tr, &h, &hvertex))
	{
		QString msg("Невозможно построить треугольник!");
		ui->msgFrame->setText(QString(msg));
		delete [] plist;
		return;
	}

	/// вывод решения в статусное окно
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
	
	/// рисование
	/// 
	
	delete [] plist;
}
