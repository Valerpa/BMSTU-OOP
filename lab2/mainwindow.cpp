#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->open_file_btn, &QPushButton::clicked, this, &MainWindow::on_open_file_clicked);
    connect(ui->check_file_btn, &QPushButton::clicked, this, &MainWindow::on_check_file_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_open_file_clicked() {
    QString file_path = QFileDialog::getOpenFileName(this, " ", "C:\\Users", "*.json");
    if (file_path.isEmpty()) {
        ui->file_path_label->setText("File was not opened");
    }
    else {
        try {
        fp = file_path.toStdString();
        ui->file_path_label->setText(file_path);
        std::string res = facade.read_operation(fp);
        ui->json_label->setText(QString::fromStdString(res));
        } catch (System_errors& ex) {
            ui->check_result_label->setText(ex.what());
        }
    }
}

void MainWindow::on_check_file_clicked() {
    std::string res = facade.read_operation(fp);
    std::string message = facade.check_operation(res);
    ui->check_result_label->setText(QString::fromStdString(message));
}

