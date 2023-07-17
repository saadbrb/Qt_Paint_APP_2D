#ifndef GRAPHOBJKT_H
#define GRAPHOBJKT_H

#include <iostream>
#include <QPointF>
#include <QPainter>
#include <QtGlobal>


class GraphObjkt
{
protected:
    QPointF firstPunkt;
    QPointF lastPunkt;
    QColor color;
    bool showOutline;
    QPointF min,max;
    bool deko;

public:
    GraphObjkt(QPointF firstPunkt_, QPointF lastPunkt_, QColor color_, bool showOutline_):
        firstPunkt(firstPunkt_), lastPunkt(lastPunkt_), color(color_), showOutline(showOutline_) {}

    GraphObjkt(QPointF firstPunkt_, QPointF lastPunkt_, QColor color_):
        firstPunkt(firstPunkt_), lastPunkt(lastPunkt_), color(color_){}

    GraphObjkt(QPointF firstPunkt_,QColor color_):
        firstPunkt(firstPunkt_),color(color_) {}
    GraphObjkt(QPointF firstPunkt_, bool deko_):
        firstPunkt(firstPunkt_),deko(deko_) {}

    GraphObjkt(const GraphObjkt&);
    explicit GraphObjkt(bool deko_ = false ): deko(deko_){}


    // Verbieten den Kopierkonstruktor und den Zuweisungsoperator
    // GraphObj(const GraphObj&) = delete;
    GraphObjkt& operator=(const GraphObjkt&) = delete;
    void setLastPunkt(QPointF p) {
        lastPunkt = p;
    }
    QPointF getFirstPunkt() const {
        return firstPunkt;
    }
    QPointF getLastPunkt() const {
        return lastPunkt;
    }
    qreal minF(qreal x, qreal y) const{
        return qMin(x, y);
    }

    qreal maxF(qreal x, qreal y) const{
        return qMax(x, y);
    }
    QColor getColor(){
        return color;
    }
    virtual void setShowOutline(bool);
    virtual void setColor(QColor);
    virtual void bewegen(QPointF punkt) = 0;
    virtual bool isNaehe(QPointF punkt) = 0;
    virtual void retation() = 0;
    virtual double getSize() = 0;
    virtual void mallen(QPainter* objkt, bool deko_) = 0;
    virtual void addPunkt(QPointF punkt_) = 0;
    virtual void calcBBox(QPointF &min, QPointF &max) const = 0;
    virtual QPointF getRefPnt() const = 0;
    virtual ~GraphObjkt() = default;
};

#endif // GRAPHOBJKT_H
