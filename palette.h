#ifndef PALETTE_H
#define PALETTE_H

#include <QImage>


class Palette
{

public:
    Palette();
    static void fillImageDefaultColorIndex(QImage* image);
    static QVector<QRgb> getDefaultColorTable();
};

#endif // PALETTE_H
