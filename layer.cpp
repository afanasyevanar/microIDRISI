#include "layer.h"
#include "palette.h"

#include <QPainter>

#include <QDebug>
#include <QLabel>
#include <QBoxLayout>

Layer::Layer(QString rstFilename, QWidget *parent) : QWidget(parent),
    photo (new IdrisiPhoto()),
    mapLabel(new QLabel())
{
    QString rdcFileName = rstFilename;
    rdcFileName.replace(".rst", ".rdc");

    photo->readRDC(rdcFileName);
    photo->readRST(rstFilename);

    uchar* matrix = photo->getMatrix();

    QImage* img = new QImage(matrix, photo->getColumns(), photo->getRows(), photo->getColumns(), QImage::Format_Indexed8);

    Palette::fillImageDefaultColorIndex(img);

    mapLabel->setPixmap(QPixmap::fromImage(*img));

    QHBoxLayout* boxLayout = new QHBoxLayout;
    boxLayout->setMargin(0);
    boxLayout->setSpacing(0);

    mapLabel->setScaledContents(true);
    mapLabel->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    mapLabel->resize(photo->getColumns(), photo->getRows());

    boxLayout->addWidget(mapLabel);
    this->setLayout(boxLayout);

    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    this->resize(100,50);

}
