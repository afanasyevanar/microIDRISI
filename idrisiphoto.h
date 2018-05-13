#ifndef IDRISIPHOTO_H
#define IDRISIPHOTO_H

#include <tuple>
#include <QtCore/QString>
#include <QMap>

class IdrisiPhoto
{
public:
    IdrisiPhoto();
    ~IdrisiPhoto();

    bool readRDC(QString filename);
    bool readRST();

private:
    std::tuple<QString, QString> parseLine(QString line);
    void extractMetadata();

private:
    int columns, rows, minValue, maxValue, displayMin, displayMax;
    QMap<QString, QString>* metadata;
};

#endif // IDRISIPHOTO_H
