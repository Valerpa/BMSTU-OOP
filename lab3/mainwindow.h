#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "facade.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QPicture>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void on_open_file_clicked();
    void on_rotate_x_clicked();
    void on_rotate_y_clicked();
    void on_rotate_z_clicked();
    void on_move_clicked();
    void on_scale_clicked();

    Ui::MainWindow *ui;
    QPicture _pixmap;
    Facade* facade;
};
#endif // MAINWINDOW_H
