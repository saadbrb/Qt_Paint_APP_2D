#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "graphobjkt.h"

class Rectangle : public GraphObjkt
{
private:
    int with;
    int height;
public:
    Rectangle(QPointF firstPunkt_, QPointF lastPunkt_, QColor color_, bool showOutline_):
        GraphObjkt(firstPunkt_, lastPunkt_, color_, showOutline_) {}

    void mallen(QPainter* objkt, bool deko_) override;
    void bewegen(QPointF punkt) override;
    bool isNaehe(QPointF punkt) override;
    void retation() override;
    double getSize() override;
    void addPunkt(QPointF punkt_) override;
    void calcBBox(QPointF &min, QPointF &max) const override;
    QPointF getRefPnt() const override;



};

#endif // RECTANGLE_H
