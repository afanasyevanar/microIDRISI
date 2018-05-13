#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

#include "idrisiphoto.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open IDRISI raster file"), QDir::homePath(), tr("IDRISI raster file (*.rst)"));

    QString rdcFileName = fileName;
    rdcFileName.replace(".rst", ".rdc");

    IdrisiPhoto photo;
    photo.readRDC(rdcFileName);
}
