#include "bboxdecorator.h"


void BBoxDecorator::mallen(QPainter* objkt, bool showAllBBox) {
    if(decoratedObj){
        decoratedObj->mallen(objkt, showAllBBox);
        if(showAllBBox){
            calcBBox(min, max);
            objkt->setPen(QPen(Qt::red, 2, Qt::DashLine));
            objkt->setBrush(Qt::NoBrush);
            objkt->drawRect(QRectF(min, max));
        }

    }
}
void BBoxDecorator::bewegen(QPointF punkt) {
    decoratedObj->bewegen(punkt);
}
void BBoxDecorator::setShowOutline(bool showOutline_)  {
    decoratedObj->setShowOutline(showOutline_);
}
void BBoxDecorator::setColor(QColor color_) {
    decoratedObj->setColor(color_);

}
bool BBoxDecorator::isNaehe(QPointF punkt){
    return decoratedObj->isNaehe(punkt);
}
void BBoxDecorator::retation() {
    decoratedObj->retation();
}
double BBoxDecorator::getSize() {
    return decoratedObj->getSize();
}
void BBoxDecorator::addPunkt(QPointF punkt_) {
    decoratedObj->addPunkt(punkt_);
}

void BBoxDecorator::calcBBox(QPointF &min, QPointF &max) const {
    decoratedObj->calcBBox(min, max);
}

QPointF BBoxDecorator::getRefPnt() const {
    return decoratedObj->getRefPnt();
}
