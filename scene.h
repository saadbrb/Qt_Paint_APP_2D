#ifndef SCENE_H
#define SCENE_H

#include <QVector>
#include <iostream>
#include "graphobjkt.h"
#include "bboxdecorator.h"

class Scene
{
private:
    QVector <GraphObjkt*> graphikObjekten;

public:
    Scene(){}
    void addObjkt(GraphObjkt* objkt, bool showAllBBox);
    void paintAllObjects(QPainter* event, bool show_all_bboxes);
    void removeAllObjects();
    void deleletOneElementIsFound(QPointF point);
    void changeColorAndOutline(QPointF point, QColor color, bool outline);
    double isFound(QPointF punkt);
    void mallAllObjectsWidthSameColor(QColor);
    void moveThisObject(double index, QPointF);
    int getObjecktSize();
    void removeThisObject(GraphObjkt*);
    GraphObjkt* getObject(int index);
    QVector <GraphObjkt*>& getGraphObjkts();

};

#endif // SCENE_H
