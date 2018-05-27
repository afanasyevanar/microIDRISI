#ifndef LAYER_H
#define LAYER_H

#include <QWidget>
#include <QLabel>

#include "idrisiphoto.h"

class Layer : public QWidget
{
    Q_OBJECT

    IdrisiPhoto* photo;
    QImage* img;
    QLabel* mapLabel;
    uchar* data;

public:
    explicit Layer(QString rstFilename, QWidget *parent = nullptr);
    ~Layer();
    void save();

signals:

public slots:
};

#endif // LAYER_H
