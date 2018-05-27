#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "layer.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QMdiSubWindow>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QAction* mapOpen = new QAction("Open File", this);
    mapOpen->setText("&Open...");
    mapOpen->setShortcut(QKeySequence("CTRL+O"));
    mapOpen->setToolTip("Open map");
    mapOpen->setStatusTip("Open map");
    mapOpen->setWhatsThis("Open map");
    connect(mapOpen, SIGNAL(triggered()), SLOT(slotLoad()));

    QAction* mapSave = new QAction("Save as png", this);
    mapSave->setText("&Save");
    mapSave->setShortcut(QKeySequence("CTRL+S"));
    mapSave->setToolTip("Save as png");
    mapSave->setStatusTip("Save as png");
    mapSave->setWhatsThis("Save as png");;
    connect(mapSave, SIGNAL(triggered()), SLOT(slotSave()));

    QMenu* fileMenu = new QMenu("&File");
    fileMenu->addAction(mapOpen);
    fileMenu->addAction(mapSave);

    fileMenu->addSeparator();
    fileMenu->addAction("&Quit",
                        this,
                        SLOT(closeAllWindows()),
                        QKeySequence("CTRL+Q")
                        );

    menuBar()->addMenu(fileMenu);

    windowsMenu = new QMenu("&Windows");
    menuBar()->addMenu(windowsMenu);
    connect(windowsMenu, SIGNAL(aboutToShow()), SLOT(slotWindows()));
    menuBar()->addSeparator();

    helpMenu = new QMenu("&Help");
    helpMenu->addAction("&About", this, SLOT(slotAbout()), Qt::Key_F1);
    menuBar()->addMenu(helpMenu);

    mdiArea = new QMdiArea();
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);

    signalMapper = new QSignalMapper(this);
    connect(signalMapper,
            SIGNAL(mapped(QWidget*)),
            this,
            SLOT(slotSetActiveSubWindow(QWidget*))
            );
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
    QMdiSubWindow *subWindow = new QMdiSubWindow();
    subWindow->setWidget(layer);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    // mdiArea.addSubWindow(layer);
    //layer->setAttribute(Qt::WA_DeleteOnClose);
    mdiArea->addSubWindow(subWindow);

    layer->show();
}

void MainWindow::slotSave()
{
    QMdiSubWindow* msw = mdiArea->activeSubWindow();
    Layer* layer = qobject_cast<Layer*>(msw->widget());

    if (layer){
        qDebug()<<layer->windowTitle();

        layer->save();
    }else {
        qDebug()<<"No active window";
    }
}

void MainWindow::slotAbout()
{
    QMessageBox::about(this, "microIDRISI", "Simple viewer of .rst files ");
}

void MainWindow::slotWindows()
{
    windowsMenu->clear();

    QAction* cascadeAction = windowsMenu->addAction("&Cascade",
                                                    mdiArea,
                                                    SLOT(cascadeSubWindows())
                                                    );
    cascadeAction->setEnabled(!mdiArea->subWindowList().isEmpty());

    QAction* tileAction = windowsMenu->addAction("&Tile",
                                                 mdiArea,
                                                 SLOT(tileSubWindows())
                                                 );
    tileAction->setEnabled(!mdiArea->subWindowList().isEmpty());

    windowsMenu->addSeparator();

    QAction* mapItem;
    QList<QMdiSubWindow*> listOfMaps = mdiArea->subWindowList();
    for (int i = 0; i < listOfMaps.size(); ++i) {
        mapItem = windowsMenu->addAction(listOfMaps.at(i)->windowTitle());
        mapItem->setCheckable(true);
        mapItem->setChecked(mdiArea->activeSubWindow() == listOfMaps.at(i));
        connect(mapItem, SIGNAL(triggered()), signalMapper, SLOT(map()));
        signalMapper->setMapping(mapItem, listOfMaps.at(i));
    }
}

void MainWindow::slotSetActiveSubWindow(QWidget *widget)
{
    if (widget) {
        mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow*>(widget));
    }
}

void MainWindow::closeAllWindows()
{
    QList<QMdiSubWindow*> listOfMaps = mdiArea->subWindowList();
    for (int i = 0; i < listOfMaps.size(); ++i) {
        listOfMaps.at(i)->close();
    }

    close();
}
