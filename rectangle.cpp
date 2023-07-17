#include <cmath>
#include "rectangle.h"

void Rectangle::mallen(QPainter* objkt, bool){
    qreal x = firstPunkt.x();
    qreal y = firstPunkt.y();
    qreal with = lastPunkt.x() - x;
    qreal height =lastPunkt.y() - y;

    objkt->setPen(QPen(color,2,Qt::SolidLine));

    if(!showOutline){
        objkt->setBrush(color);
    } else{
        objkt->setBrush(Qt::NoBrush);
    }
    objkt->drawRect(QRectF(x,y,with,height));
}

void Rectangle::bewegen(QPointF punkt) {
    QPointF tpr = punkt - firstPunkt;
    firstPunkt += tpr;
    lastPunkt += tpr;
}


bool Rectangle::isNaehe(QPointF punkt){

    qreal minX = minF(firstPunkt.x(), lastPunkt.x());
    qreal minY = minF(firstPunkt.y(), lastPunkt.y());
    qreal maxX = maxF(firstPunkt.x(), lastPunkt.x());
    qreal maxY = maxF(firstPunkt.y(), lastPunkt.y());

    return (minX <= punkt.x() && punkt.x() <= maxX) &&
            (minY <= punkt.y() && punkt.y() <= maxY);
}

void Rectangle::retation(){
    //TODO
}

double Rectangle::getSize(){

    return std::hypot(firstPunkt.x() - lastPunkt.x(), firstPunkt.y() - lastPunkt.y());

}

void Rectangle::addPunkt(QPointF punkt_) {

    //Diese funktion ist nur fuer Polyline geeignet
}
void Rectangle::calcBBox(QPointF &min, QPointF &max) const  {
    min.setX(minF(firstPunkt.x(), lastPunkt.x()));
    min.setY(minF(firstPunkt.y(), lastPunkt.y()));
    max.setX(maxF(firstPunkt.x(), lastPunkt.x()));
    max.setY(maxF(firstPunkt.y(), lastPunkt.y()));
}

QPointF Rectangle::getRefPnt() const {
    return (firstPunkt + lastPunkt) / 2.0;
}
