#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
    "/Downloads",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

}


