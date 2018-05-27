#include "layer.h"
#include "palette.h"

#include <QPainter>

#include <QDebug>
#include <QLabel>
#include <QBoxLayout>
#include <QFileDialog>

Layer::Layer(QString rstFilename, QWidget *parent) : QWidget(parent),
    photo (new IdrisiPhoto()),
    mapLabel(new QLabel())
{
    qDebug()<<"Layer constructor";
    QString rdcFileName = rstFilename;
    rdcFileName.replace(".rst", ".rdc");

    photo->readRDC(rdcFileName);
    photo->readRST(rstFilename);

    setWindowTitle(photo->getMapName());

    data = photo->getMatrix();

    img = new QImage(data, photo->getColumns(), photo->getRows(), photo->getColumns(), QImage::Format_Indexed8);

    Palette::fillImageDefaultColorIndex(img);

    mapLabel->resize(photo->getColumns()/5, photo->getRows()/5);
    mapLabel->setPixmap(QPixmap::fromImage(*img));

    QHBoxLayout* boxLayout = new QHBoxLayout;
    boxLayout->setMargin(0);
    boxLayout->setSpacing(0);

    mapLabel->setScaledContents(true);
    mapLabel->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);


    boxLayout->addWidget(mapLabel);
    this->setLayout(boxLayout);

    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);


}

Layer::~Layer()
{
    qDebug()<<"Layer destructor";
    delete photo;
    delete img;
    delete mapLabel;
}

void Layer::save()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Idrisi map as picture"), QDir::homePath(), tr("JPG file (*.jpg)") );

    img->save(fileName, "jpg", 100);
}
