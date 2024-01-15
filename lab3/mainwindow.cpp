#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->open_file_btn, &QPushButton::clicked, this, &MainWindow::on_open_file_clicked);
    connect(ui->rotate_x_btn, &QPushButton::clicked, this, &MainWindow::on_rotate_x_clicked);
    connect(ui->rotate_y_btn, &QPushButton::clicked, this, &MainWindow::on_rotate_y_clicked);
    connect(ui->rotate_z_btn, &QPushButton::clicked, this, &MainWindow::on_rotate_z_clicked);
    connect(ui->move_btn, &QPushButton::clicked, this, &MainWindow::on_move_clicked);
    connect(ui->scale_btn, &QPushButton::clicked, this, &MainWindow::on_scale_clicked);
    QMessageBox::information(this, "Attention", "Enter normalization parameters before opening file!");
    _pixmap = QPicture();
    facade = new Facade(_pixmap);
    _pixmap.setBoundingRect(QRect(QPoint(0, 0), QPoint(ui->model_label->width(), ui->model_label->height())));
}

MainWindow::~MainWindow()
{
    delete facade;
    delete ui;
}

void MainWindow::on_open_file_clicked() {
    QString file_path = (QFileDialog::getOpenFileName(this, tr("Open File"), "C://", "*.csv"));
    if (file_path.isEmpty()) {
        ui->file_path_label->setText("File was not chosen");
        return;
    }
    ui->file_path_label->setText(file_path);
    std::string fp = file_path.toStdString();
    Normalization_parameters params = Normalization_parameters(ui->max_norm_edit->text().toFloat(), ui->min_norm_edit->text().toFloat(), ui->norm_step_edit->text().toFloat(), ui->norm_step_edit->text().toFloat());
    Facade_operation_result result = facade->load_scene(fp, params);
    if (!result.is_success()) {
        std::string error = result.get_error_message();
        const char* err = error.c_str();
        QMessageBox::critical(this, "Error", err);
        return;
    }
    result = facade->rotate_scene(60, 0, 0);
    facade->draw_scene();
    ui->model_label->setPicture(_pixmap);
}

void MainWindow::on_rotate_x_clicked() {
    Facade_operation_result res = facade->rotate_scene(ui->rotate_x_edit->text().toFloat(), 0, 0);
    if (!res.is_success()) {
        std::string error = res.get_error_message();
        const char* err = error.c_str();
        QMessageBox::critical(this, "Error", err);
        return;
    }
    facade->draw_scene();
    ui->model_label->setPicture(_pixmap);
}

void MainWindow::on_rotate_y_clicked() {
    Facade_operation_result res = facade->rotate_scene(0, ui->rotate_y_edit->text().toFloat(), 0);
    if (!res.is_success()) {
        std::string error = res.get_error_message();
        const char* err = error.c_str();
        QMessageBox::critical(this, "Error", err);
        return;
    }
    facade->draw_scene();
    ui->model_label->setPicture(_pixmap);
}

void MainWindow::on_rotate_z_clicked() {
    Facade_operation_result res = facade->rotate_scene(0, 0, ui->rotate_z_edit->text().toFloat());
    if (!res.is_success()) {
        std::string error = res.get_error_message();
        const char* err = error.c_str();
        QMessageBox::critical(this, "Error", err);
        return;
    }
    facade->draw_scene();
    ui->model_label->setPicture(_pixmap);
}

void MainWindow::on_move_clicked() {
    Facade_operation_result res = facade->move_scene(ui->move_x_edit->text().toFloat(), -ui->move_y_edit->text().toFloat(), ui->move_z_edit->text().toFloat());
    if (!res.is_success()) {
        std::string error = res.get_error_message();
        const char* err = error.c_str();
        QMessageBox::critical(this, "Error", err);
        return;
    }
    facade->draw_scene();
    ui->model_label->setPicture(_pixmap);
}

void MainWindow::on_scale_clicked() {
    Facade_operation_result res = facade->scale_scene(ui->scale_x_edit->text().toFloat(), ui->scale_y_edit->text().toFloat(), ui->scale_z_edit->text().toFloat());
    if (!res.is_success()) {
        std::string error = res.get_error_message();
        const char* err = error.c_str();
        QMessageBox::critical(this, "Error", err);
        return;
    }
    facade->draw_scene();
    ui->model_label->setPicture(_pixmap);
}
