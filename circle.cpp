#include <cmath>
#include "circle.h"

void Circle::mallen(QPainter* objkt, bool){
    rad = std::hypot(firstPunkt.x() - lastPunkt.x(), firstPunkt.y() - lastPunkt.y());
    objkt->setPen(QPen(color, 2, Qt::SolidLine));
    if(!showOutline){
        objkt->setBrush(color);
    }
    else {
        objkt->setBrush(Qt::NoBrush);
    }
    double x = firstPunkt.x() - rad;
    double y = firstPunkt.y() - rad;
    double diameter = rad * 2;

    objkt->drawEllipse(QRectF(x, y, diameter, diameter));
}

void Circle::bewegen(QPointF punkt) {
    QPointF tpr = punkt - firstPunkt;
    firstPunkt += tpr;
    lastPunkt += tpr;
}

void Circle::calcBBox(QPointF &min, QPointF &max) const  {
    min.setX(firstPunkt.x() - rad);
    min.setY(firstPunkt.y() - rad);
    max.setX(firstPunkt.x() + rad);
    max.setY(firstPunkt.y() + rad);
}

bool Circle::isNaehe(QPointF punkt){
    double distance = std::hypot(firstPunkt.x() - punkt.x(), firstPunkt.y() - punkt.y());
    return distance <= rad;
}

void Circle::retation(){
    //TODO
}

double Circle::getSize(){
    return rad;
}

void Circle::addPunkt(QPointF punkt_) {

    //Diese funktion ist nur fuer Polyline geeignet
}

QPointF Circle::getRefPnt() const {
    return firstPunkt;
}
