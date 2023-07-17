#include <cmath>
#include "line.h"


void Line::mallen(QPainter* objkt, bool deko_) {
    objkt->setPen(QPen(color,2,Qt::SolidLine));

    objkt->drawLine(firstPunkt, lastPunkt);

}
void Line::bewegen(QPointF punkt) {
    QPointF tpr = punkt - firstPunkt;

    firstPunkt += tpr;
    lastPunkt += tpr;
}

void Line::calcBBox(QPointF &min_, QPointF &max_) const  {
    qreal minX = minF(firstPunkt.x(), lastPunkt.x());
    qreal minY = minF(firstPunkt.y(), lastPunkt.y());
    qreal maxX = maxF(firstPunkt.x(), lastPunkt.x());
    qreal maxY = maxF(firstPunkt.y(), lastPunkt.y());

    min_.setX(minX);
    min_.setY(minY);
    max_.setX(maxX);
    max_.setY(maxY);
}

bool Line::isNaehe(QPointF punkt) {
    // Calculate the distances from the point to the endpoints of the line
    double d1 = std::hypot(punkt.x() - firstPunkt.x(), punkt.y() - firstPunkt.y());
    double d2 = std::hypot(punkt.x() - lastPunkt.x(), punkt.y() - lastPunkt.y());

    // Calculate the length of the line
    double lineLength = std::hypot(firstPunkt.x() - lastPunkt.x(), firstPunkt.y() - lastPunkt.y());

    // Define a tolerance (this might need to be adjusted based on  specific use case)
    const double tolerance = 1.0;

    // The point is on (or very close to) the line if the sum of d1 and d2 is equal to the line length within the tolerance
    return std::abs(d1 + d2 - lineLength) < tolerance;
}
void Line::retation() {
    //TODO
}
double Line::getSize() {
    return std::hypot(firstPunkt.x() - lastPunkt.x(), firstPunkt.y() - lastPunkt.y());
}

void Line::addPunkt(QPointF punkt_) {

    //Diese funktion ist nur fuer Polyline geeignet
}

QPointF Line::getRefPnt() const {
    return (firstPunkt + lastPunkt) / 2.0;
}
