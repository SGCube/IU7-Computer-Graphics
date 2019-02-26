#include <QTableWidget>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "draw.h"

#include "solve.h"
#include "triangle.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	
	QGraphicsScene *scene = new QGraphicsScene(this);
	ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addButton_released()
{
	// флаг корректности данных
	bool correct = true;
	// строки для хранения содержимого полей ввода
    QString xstr = ui->xEdit->text();
	QString ystr = ui->yEdit->text();
	// координаты точки
	float x, y;
	x = xstr.toFloat(&correct);
	if (!correct)
	{
		error_valmsg(ui->msgFrame, 0);
		return;
	}
	y = ystr.toFloat(&correct);
	if (!correct)
	{
		error_valmsg(ui->msgFrame, 1);
		return;
	}
	
	xstr = QString::number(x);
	ystr = QString::number(y);
	
	ui->xEdit->clear();
	ui->yEdit->clear();
	
    ui->pointTable->insertRow(ui->pointTable->rowCount());
	int row = ui->pointTable->rowCount() - 1;
	QTableWidgetItem *xitem = new QTableWidgetItem(xstr);
	QTableWidgetItem *yitem = new QTableWidgetItem(ystr);
	ui->pointTable->setItem(row, 0, xitem);
	ui->pointTable->setItem(row, 1, yitem);
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
	ui->graphicsView->scene()->clear();
    int rows = ui->pointTable->rowCount();	// количество точек (строк таблицы)
	QPointF *plist = NULL;					// список точек
	
    /// проверка на достаточность
    if (rows < 3)
    {
        error_msg(ui->msgFrame, ERR_PLIST_N);
        return;
    }
	
	/// получение набора точек
	int rc = get_plist(ui->pointTable, &plist, rows);
	if (rc != OK)
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
		draw(ui->graphicsView->scene(), &tr, plist, rows);
	}
	
	delete [] plist;
}

void MainWindow::on_clearButton_released()
{
    ui->graphicsView->scene()->clear();
}
