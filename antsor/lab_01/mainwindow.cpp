#include <QTableWidget>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "painterwidget.h"

#include "solve.h"
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
        error_msg(ui->msgFrame, ERR_PLIST_N);
        return;
    }
	
	/// получение списка точек
	int no = -1;		// номер некорректной точки
	bool coord = 0;		// некорректная координата (0 - X, 1 - Y)
	int rc = get_plist(ui->pointTable, &plist, rows, &no, &coord);
	if (rc == ERR_PLIST_VAL)
	{
        error_valmsg(ui->msgFrame, no, coord);
		return;
	}
	else if (rc != OK)
	{
		error_msg(ui->msgFrame, rc);
		return;
	}
	
	/// решение задачи
	Triangle tr;		// треугольник решения
	QVector2D h;		// наименьшая высота
	QPointF hvertex;	// вершина наименьшей высоты
	
	if (!solve(plist, rows, &tr, &h, &hvertex))
		error_msg(ui->msgFrame, ERR_SOLV_NONE);
	else
	{
		/// вывод решения в статусное окно
		solution_msg(ui->msgFrame, &tr, &h, &hvertex);
		
		/// рисование решения
		/// 
		ui->painterW->drawTriangle(&tr);
		ui->painterW->drawPoints(plist, rows);
	}
	
	delete [] plist;
}
