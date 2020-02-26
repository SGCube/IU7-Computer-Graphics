#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_addButton_released();

    void on_delAllButton_released();

    void on_delButton_released();

    void on_drawButton_released();

	void on_clearButton_released();
	
	void on_pointTable_cellPressed(int row);
	
	void on_editButton_pressed();
	
	void on_editButton_released();
	
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
