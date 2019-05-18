#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QColor>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int xc = 0;
    int yc = 0;

private slots:
    void on_cir_build_clicked();

    void on_pushButton_2_clicked();

    void on_cir_build_2_clicked();

    void on_el_build_clicked();

    void on_el_build_sp_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QColor *c;
};

#endif // MAINWINDOW_H
