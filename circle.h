#ifndef CIRCLE_H
#define CIRCLE_H

#include "graphobjkt.h"
#include <cmath>

class Circle : public GraphObjkt
{
private:
    double rad;

public:

    Circle(QPointF firstPunkt_, QPointF lastPunkt_, QColor color_, bool showOutline_):
        GraphObjkt(firstPunkt_, lastPunkt_, color_, showOutline_) {
        rad = std::hypot(firstPunkt.x() - lastPunkt.x(), firstPunkt.y() - lastPunkt.y());
    }

    void mallen(QPainter* objkt, bool deko_) override;
    void bewegen(QPointF punkt) override;
    bool isNaehe(QPointF punkt) override;
    void retation() override;
    double getSize() override;
    void calcBBox(QPointF &min, QPointF &max) const override;
    void addPunkt(QPointF punkt_) override;
    QPointF getRefPnt() const override;

};

#endif // CIRCLE_H
