#ifndef LINE_H
#define LINE_H

#include "graphobjkt.h"

class Line : public GraphObjkt
{
public:
    Line(QPointF firstPunkt_, QPointF lastPunkt_, QColor color_):
        GraphObjkt(firstPunkt_, lastPunkt_, color_) {}

    void mallen(QPainter* objkt, bool deko_) override;
    void bewegen(QPointF punkt) override;
    bool isNaehe(QPointF punkt) override;
    void retation() override;
    double getSize() override;
    void addPunkt(QPointF punkt_) override;
    void calcBBox(QPointF &min, QPointF &max) const override;
    QPointF getRefPnt() const override;


};

#endif // LINE_H
