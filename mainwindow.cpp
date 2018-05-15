#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

#include "idrisiphoto.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QAction* mapOpen = new QAction("Open File", 0);
    mapOpen->setText("&Open...");
    mapOpen->setShortcut(QKeySequence("CTRL+O"));
    mapOpen->setToolTip("Open map");
    mapOpen->setStatusTip("Open map");
    mapOpen->setWhatsThis("Open map");
    //mapOpen->setIcon(QPixmap(":/fileopen.png"));
    connect(mapOpen, SIGNAL(triggered()), SLOT(slotLoad()));

    ui->setupUi(this);

    QMenu* fileMenu = new QMenu("&File");
    fileMenu->addAction(mapOpen);

    menuBar()->addMenu(fileMenu);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotLoad()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open IDRISI raster file"), QDir::homePath(), tr("IDRISI raster file (*.rst)"));

    QString rdcFileName = fileName;
    rdcFileName.replace(".rst", ".rdc");

    IdrisiPhoto photo;
    photo.readRDC(rdcFileName);
}
