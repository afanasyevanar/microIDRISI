#include "palette.h"

#include <QFile>
#include <QtDebug>
#include <QColor>
#include <QRgb>

const QString defaultPalettePath=":/IDRIS256.SMP";

void Palette::fillImageDefaultColorIndex(QImage *image)
{
    QFile file (defaultPalettePath);
    if (!file.open(QIODevice::ReadOnly)){
        qDebug()<<"Can't open default palette file";
    }

    QByteArray idrisi = file.read(8);
    QByteArray something =  file.read(10); // Неизвестно что это и зачем.
    // Судя по всему, это заголовок палитры и он всегда одинаковый
    //qDebug()<<idrisi;
    //qDebug()<<something;

    if (file.bytesAvailable() != 768){
        qDebug()<<"Aveilable bytes in palette file: "<<file.bytesAvailable() <<" - is wrong, must be 768";
    }
    for (qint64 i=0; i< file.bytesAvailable(); i++){
        QByteArray color = file.read(3);
        image->setColor(i, qRgb(color.at(0)&0xFF, color.at(1)&0xFF, color.at(2)&0xFF));
    }

}

QVector<QRgb> Palette::getDefaultColorTable()
{
    QVector<QRgb> vector;

    QFile file (defaultPalettePath);
    if (!file.open(QIODevice::ReadOnly)){
        qDebug()<<"Can't open default palette file";
    }

    QByteArray idrisi = file.read(8);
    QByteArray something =  file.read(10);

    if (file.bytesAvailable() != 768){
        qDebug()<<"Aveilable bytes in palette file: "<<file.bytesAvailable() <<" - is wrong, must be 768";
    }
    for (qint64 i=0; i< file.bytesAvailable(); i++){
        QByteArray color = file.read(3);
        vector<<qRgb(color.at(0)&0xFF, color.at(1)&0xFF, color.at(2)&0xFF);
    }

    return vector;
}
