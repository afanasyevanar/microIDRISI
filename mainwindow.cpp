#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

#include "layer.h"

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

    mdiArea = new QMdiArea();
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotLoad()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open IDRISI raster file"), QDir::homePath(), tr("IDRISI raster file (*.rst)"));

   Layer* layer = new Layer(fileName);
   layer->setAttribute(Qt::WA_DeleteOnClose);
   mdiArea->addSubWindow(layer);
   layer->show();


}
