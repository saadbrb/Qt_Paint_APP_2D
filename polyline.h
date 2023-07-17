#ifndef POLYLINE_H
#define POLYLINE_H

#include <QVector>
#include <QPointF>
#include "polygone.h"

class Polyline : public Polygone
{
public:
    Polyline(QPointF firstPunkt_, QColor color_):
        Polygone(firstPunkt_, firstPunkt_, color_, false) {}

    void mallen(QPainter* objkt, bool deko_) override;
    bool isNaehe(QPointF punkt) override;

};

#endif // POLYLINE_H
