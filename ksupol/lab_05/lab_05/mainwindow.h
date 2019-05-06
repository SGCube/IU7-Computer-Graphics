#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "paint.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QColor>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    int amount = 0;
    struct point points[100];
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_add_poin_clicked();
    void insert_into_table(QString x, QString y);

    void on_lock_clicked();

    void on_clear_clicked();

    void on_clear_table_clicked();

    void clear_array();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QColor *c;
};

#endif // MAINWINDOW_H
