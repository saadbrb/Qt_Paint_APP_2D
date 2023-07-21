#ifndef SCENE_H
#define SCENE_H

#include <QVector>
#include <iostream>
#include "graphobjkt.h"
#include "bboxdecorator.h"

class Scene
{
private:
    QVector <std::shared_ptr<GraphObjkt>> graphikObjekten;

public:
    Scene(){}
    void addObjkt(std::shared_ptr<GraphObjkt> objkt, bool showAllBBox);
    void paintAllObjects(QPainter* event, bool show_all_bboxes);
    void removeAllObjects();
    void deleletOneElementIsFound(QPointF point);
    std::shared_ptr<GraphObjkt> changeColorAndOutline(QPointF point, QColor color, bool outline);
    double isFound(QPointF punkt);
    void mallAllObjectsWidthSameColor(QColor);
    void moveThisObject(double index, QPointF);
    int getObjecktSize();
    void removeThisObject(std::shared_ptr<GraphObjkt>);
    std::shared_ptr<GraphObjkt> getObject(int index);
    QVector<std::shared_ptr<GraphObjkt>> getGraphObjkts();

};

#endif // SCENE_H
