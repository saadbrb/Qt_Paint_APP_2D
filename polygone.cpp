#include <cmath>
#include "polygone.h"
#include "line.h"


void Polygone::mallen(QPainter* painter, bool){
    painter->setPen(QPen(color,2,Qt::SolidLine));
    QPolygonF polygon;
    polygon << punkten;
    if(!showOutline){
        painter->setBrush(color);
    } else{
        painter->setBrush(Qt::NoBrush);
    }

    // Zeichnen  des Polygons
    painter->drawPolygon(polygon);
}

void Polygone::bewegen(QPointF punkt) {
    QPointF tpr = punkt - punkten.front();

    for(QPointF& p : punkten){
        p += tpr;
    }
}
void Polygone::calcBBox(QPointF &min_, QPointF &max_) const  {
    qreal minX = punkten[0].x(), minY = punkten[0].y();
    qreal maxX = minX, maxY = minY;

    for (const QPointF &p : punkten) {
        minX = minF(minX, p.x());
        minY = minF(minY, p.y());
        maxX = maxF(maxX, p.x());
        maxY = maxF(maxY, p.y());
    }

    min_.setX(minX);
    min_.setY(minY);
    max_.setX(maxX);
    max_.setY(maxY);
}


bool Polygone::isNaehe(QPointF punkt){
    QPolygonF polygon;
    polygon << punkten;
    return polygon.containsPoint(punkt, Qt::OddEvenFill);
}

void Polygone::retation(){
    //TODO
}

double Polygone::getSize(){
    double distanceMax = std::hypot(firstPunkt.x() - lastPunkt.x(), firstPunkt.y() - lastPunkt.y());
    for (int i=2; i<punkten.size()-1; i++) {
        double distance = std::hypot(punkten[i].x() - punkten[i+1].x(), punkten[i].y() - punkten[i-1].y());
        if(distance > distanceMax){
            distanceMax = distance;
        }
    }
    return distanceMax;
}

void Polygone::addPunkt(QPointF punkt_) {
    punkten.push_back(punkt_);
}
bool Polygone::isNear(const QPointF& a) {
    return std::hypot(a.x() - punkten[0].x(), a.y() - punkten[0].y()) <= 10;
}

QPointF Polygone::getRefPnt() const {
    QPointF res;
    for(const QPointF& p : punkten){
        res += p;
    }
    return res / punkten.size();
}
