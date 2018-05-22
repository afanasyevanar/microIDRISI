#ifndef LAYER_H
#define LAYER_H

#include <QWidget>
#include <QLabel>

#include "idrisiphoto.h"

class Layer : public QWidget
{
    Q_OBJECT

    IdrisiPhoto* photo;
    QLabel* mapLabel;

public:
    explicit Layer(QString rstFilename, QWidget *parent = nullptr);

signals:

public slots:
};

#endif // LAYER_H
