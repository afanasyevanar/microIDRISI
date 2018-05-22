#include "idrisiphoto.h"

#include <iostream>

#include <QFile>
#include <QtDebug>
#include <QStringList>

IdrisiPhoto::IdrisiPhoto():
    columns(0),
    rows(0),
    minValue(0),
    maxValue(0),
    displayMin(0),
    displayMax(0),
    metadata{new QMap<QString,QString>()}
{

}

IdrisiPhoto::~IdrisiPhoto()
{
    qDebug()<<"I am destructor";

    auto iterator = metadata->constBegin();
    while (iterator != metadata->constEnd()){
        qDebug() << iterator.key() << ": " << iterator.value();
        ++iterator;
    }
    delete metadata;
}

bool IdrisiPhoto::readRDC(QString rdcFilename)
{
    QFile rdcFile(rdcFilename);

    if (!rdcFile.exists()){
        qDebug()<<"Metadata file (.rdc) "<<rdcFilename<<" doesn't exists";
        return false;
    }

    if (!rdcFile.open(QIODevice::ReadOnly)){
        qDebug()<<"Error while opening file "<<rdcFilename;
        return false;
    }

    char line[1024];
    qint64 lineLength;

    QString key, value;

    while (!rdcFile.atEnd()){
        lineLength= rdcFile.readLine(line, sizeof(line));
        if (lineLength != -1) {
            std::tie(key,value) = parseLine(QString::fromLocal8Bit(line, lineLength));
           // if (metadata->contains(key)){
                metadata->insertMulti(key, value);
            //}else{
             //   metadata->insert(key,value);
            //}
        }
    }
    rdcFile.close();

    extractMetadata();

    return true;
}

bool IdrisiPhoto::readRST(QString rstFilename)
{
    QFile rstFile(rstFilename);

    if (!rstFile.exists()){
        qDebug()<<"Data file (.rst) "<<rstFilename<<" doesn't exists";
        return false;
    }

    if (!rstFile.open(QIODevice::ReadOnly)){
        qDebug()<<"Error while opening file "<<rstFilename;
        return false;
    }


   matrix = new QByteArray(rstFile.readAll());

   if (matrix->length() != columns*rows){
       qDebug()<<"Wrong size or amount of data: "<<matrix->length()
              <<" != "<<columns*rows;
   }

    rstFile.close();

    return true;
}

std::tuple<QString, QString> IdrisiPhoto::parseLine(QString line)
{
    int semicolonIndex = line.indexOf(':');

    return std::make_tuple(line.left(semicolonIndex).trimmed(), line.right(line.size() - semicolonIndex - 1).trimmed());

}

void IdrisiPhoto::extractMetadata()
{
    if (metadata->contains("columns")){
        columns = metadata->value("columns").toInt();
    }
    if (metadata->contains("rows")){
        rows = metadata->value("rows").toInt();
    }
    if (metadata->contains("min. value")){
        minValue = metadata->value("min. value").toInt();
    }
    if (metadata->contains("max. value")){
        maxValue = metadata->value("max. value").toInt();
    }
    if (metadata->contains("display min")){
        displayMin = metadata->value("display min").toInt();
    }
    if (metadata->contains("display max")){
        displayMax = metadata->value("display max").toInt();
    }
}

uchar* IdrisiPhoto::getMatrix() const
{
    uchar* resultMatrix = new uchar[matrix->size()];
    for (long i=0; i<matrix->size(); i++){
        resultMatrix[i] = matrix->data()[i];
       // qDebug()<<(int)matrix->data()[i]<<" = "<<resultMatrix[i];
    }
    return resultMatrix;
}

int IdrisiPhoto::getDisplayMax() const
{
    return displayMax;
}

int IdrisiPhoto::getDisplayMin() const
{
    return displayMin;
}

int IdrisiPhoto::getMaxValue() const
{
    return maxValue;
}

int IdrisiPhoto::getMinValue() const
{
    return minValue;
}

int IdrisiPhoto::getRows() const
{
    return rows;
}

int IdrisiPhoto::getColumns() const
{
    return columns;
}
