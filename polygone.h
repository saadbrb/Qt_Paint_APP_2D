#ifndef POLYGONE_H
#define POLYGONE_H

#include <QVector>
#include "graphobjkt.h"

class Polygone : public GraphObjkt
{
protected:
    QVector <QPointF> punkten;
public:
    Polygone(QPointF firstPunkt_, QPointF lastPunkt_, QColor color_, bool showOutline_):
        GraphObjkt(firstPunkt_, lastPunkt_, color_, showOutline_) {
        punkten.push_back(firstPunkt);
        punkten.push_back(lastPunkt);
    }

    bool isNear(const QPointF& a);
    void mallen(QPainter* objkt, bool deko_) override;
    void bewegen(QPointF punkt) override;
    bool isNaehe(QPointF punkt) override;
    void retation() override;
    double getSize() override;
    void addPunkt(QPointF punkt_) override;
    void calcBBox(QPointF &min, QPointF &max) const override;
    QPointF getRefPnt() const override;

};

#endif // POLYGONE_H
