#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "painterwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
	PainterWidget *painterW;
    ~MainWindow();

private slots:
    void on_addButton_released();

    void on_delAllButton_released();

    void on_delButton_released();

    void on_drawButton_released();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
