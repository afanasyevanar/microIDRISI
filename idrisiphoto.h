#ifndef IDRISIPHOTO_H
#define IDRISIPHOTO_H

#include <tuple>
#include <QString>
#include <QMap>

class IdrisiPhoto
{
public:
    IdrisiPhoto();
    ~IdrisiPhoto();

    bool readRDC(QString rdcFilename);
    bool readRST(QString rstFilename);

    int getColumns() const;
    int getRows() const;
    int getMinValue() const;
    int getMaxValue() const;
    int getDisplayMin() const;
    int getDisplayMax() const;

    uchar* getMatrix() const;

private:
    std::tuple<QString, QString> parseLine(QString line);
    void extractMetadata();

private:
    int columns, rows, minValue, maxValue, displayMin, displayMax;
    QMap<QString, QString>* metadata;
    QByteArray* matrix;
};

#endif // IDRISIPHOTO_H
