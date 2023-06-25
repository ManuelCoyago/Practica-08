#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include <QFileSystemModel>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
QFileSystemModel *fileModel;
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
     "/Downloads",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!dir.isEmpty()) {
        ui->lineEdit->setText(dir);

        // Crear el modelo del sistema de archivos y configurar la ruta del directorio seleccionado
        fileModel = new QFileSystemModel(this);
        fileModel->setRootPath(dir);

        // Establecer el modelo en el QTreeView
        ui->treeView->setModel(fileModel);
        ui->treeView->setRootIndex(fileModel->index(dir));

        // Obtener la información del directorio y sus archivos
        QDir directory(dir);
        QString directoryInfo = "Ruta del directorio: " + directory.path() + "\n\n";
        directoryInfo += "Contenidos del directorio:\n";

        QStringList entries = directory.entryList(QDir::AllEntries | QDir::NoDotAndDotDot);
        foreach (QString entry, entries) {
            QFileInfo fileInfo(directory.filePath(entry));
            QString fileProperties = fileInfo.fileName() + "\n";
            fileProperties += "Tamaño: " + QString::number(fileInfo.size()) + " bytes\n";
            fileProperties += "Ultima modificacion: " + fileInfo.lastModified().toString() + "\n";
            fileProperties += "Permisos: " + QString::number(fileInfo.permissions()) + "\n";
            // Agrega más propiedades según sea necesario
            directoryInfo += fileProperties + "\n";
        }

        ui->plainTextEdit->setPlainText(directoryInfo);
        ui->plainTextEdit->setReadOnly(true);
    }
}

