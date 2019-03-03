#include <QTableWidget>
#include <QMouseEvent>

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
	
	ui->editButton->setDisabled(true);
	ui->delButton->setDisabled(true);
	ui->delAllButton->setDisabled(true);
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
	
	ui->delAllButton->setDisabled(false);
}

void MainWindow::on_editButton_pressed()
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
	
	int row = ui->pointTable->currentRow();
	
	QTableWidgetItem *xitem = new QTableWidgetItem(xstr);
	QTableWidgetItem *yitem = new QTableWidgetItem(ystr);
	ui->pointTable->setItem(row, 0, xitem);
	ui->pointTable->setItem(row, 1, yitem);
}

void MainWindow::on_delAllButton_released()
{
	while (ui->pointTable->rowCount() > 0)
		ui->pointTable->removeRow(ui->pointTable->rowCount() - 1);
	
	ui->xEdit->clear();
	ui->yEdit->clear();
	
	ui->editButton->setDisabled(true);
	ui->delButton->setDisabled(true);
	ui->delAllButton->setDisabled(true);
}

void MainWindow::on_delButton_released()
{
    ui->pointTable->removeRow(ui->pointTable->currentRow());
	ui->pointTable->clearFocus();
	
	ui->xEdit->clear();
	ui->yEdit->clear();
	
	ui->editButton->setDisabled(true);
	ui->delButton->setDisabled(true);
	if (ui->pointTable->rowCount() == 0)
		ui->delAllButton->setDisabled(true);
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
	list_t *res = solve(plist, rows);	// список решений
	
	if (!res)
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

void MainWindow::on_pointTable_cellPressed(int row)
{
	ui->xEdit->clear();
	ui->yEdit->clear();
	
	ui->xEdit->setText(ui->pointTable->item(row, 0)->text());
	ui->yEdit->setText(ui->pointTable->item(row, 1)->text());
	
	ui->editButton->setDisabled(false);
	ui->delButton->setDisabled(false);
}
