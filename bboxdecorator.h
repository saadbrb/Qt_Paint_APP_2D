#ifndef BBOXDECORATOR_H
#define BBOXDECORATOR_H
#include "graphobjkt.h"

class BBoxDecorator : public GraphObjkt
{
private:

    GraphObjkt* decoratedObj;

public:
    BBoxDecorator(GraphObjkt* obj, bool deko_ ) : GraphObjkt(obj->getFirstPunkt(), deko_),
        decoratedObj(obj) {}
    void mallen(QPainter* objkt, bool schowAllBBox) override;
    void bewegen(QPointF punkt) override;
    bool isNaehe(QPointF punkt) override;
    void retation() override;
    double getSize() override;
    void addPunkt(QPointF punkt_) override;
    void calcBBox(QPointF &min, QPointF &max) const override;
    void setShowOutline(bool) override;
    void setColor(QColor) override;
    QPointF getRefPnt() const override;
};

#endif // BBOXDECORATOR_H
