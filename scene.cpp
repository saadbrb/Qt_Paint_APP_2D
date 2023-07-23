#include "scene.h"


void Scene::addObjkt(GraphObjkt* objkt, bool showAllBBox){
    //    if(objkt->getSize() >= 2)   {
    graphikObjekten.push_back(new BBoxDecorator(objkt, showAllBBox));
    std::cout<<"objket added secessful!\n";
    std::cout<<"Size is :  "<<graphikObjekten.size()<<"\n";
    //    }
    //    else {
    //        std::cout<<"Size ist klein! Not added possible!\n";
    //    }
}
void Scene::paintAllObjects(QPainter* event, bool show_all_bboxes){
    for(GraphObjkt* objkt : graphikObjekten){
        objkt->mallen(event, show_all_bboxes);
    }
}

void Scene::deleletOneElementIsFound(QPointF point){
    if(graphikObjekten.size() > 0){
        GraphObjkt* objectToDelete = nullptr;
        for(GraphObjkt* objkt : graphikObjekten){
            if(objkt->isNaehe(point)){
                objectToDelete = objkt;
                break; // Beendet die Schleife, sobald das Objekt gefunden wurde
            }
        }

        // Löscht das gefundene Objekt aus der Liste
        if(objectToDelete != nullptr){
            graphikObjekten.removeOne(objectToDelete);
            delete objectToDelete; // Optional, wenn dynamische Speicherverwaltung verwendet wird
            std::cout<<"Delete von Element war erfolgreich!\n";
        }
    }
}
GraphObjkt* Scene::changeColorAndOutline(QPointF point, QColor color, bool outline){
    if(graphikObjekten.size() > 0){
        for(int i=0; i<graphikObjekten.size(); i++ ){
            if(graphikObjekten[i]->isNaehe(point)){
                graphikObjekten[i]->setColor(color);
                graphikObjekten[i]->setShowOutline(outline);
                std::cout<<"Changed ok!\n";
                return graphikObjekten[i];
            }
        }
    }
    return nullptr;
}
double Scene::isFound(QPointF punkt){
    if(graphikObjekten.size() > 0){
        for(double i=0; i<graphikObjekten.size(); i++){
            if(graphikObjekten[i]->isNaehe(punkt)){
                std::cout<<"Element is Found!\n";
                return i;
            }
        }
    }
    return -1;
}
void Scene::moveThisObject(double index, QPointF punkt){
    if(graphikObjekten.size() > 0 && 0 <= index && index < graphikObjekten.size()){
        graphikObjekten[index]->bewegen(punkt);
    }
}

void Scene::removeAllObjects(){
    if(graphikObjekten.size() > 0){
        for (GraphObjkt* object : graphikObjekten) {
            // Löschen Sie das durch den Zeiger referenzierte Objekt
            delete object;
        }

        // Leeren Sie den Vektor
        graphikObjekten.clear();
    }
}
void Scene::removeThisObject(GraphObjkt* object_){
    bool found = false;
    for (GraphObjkt* object : graphikObjekten) {
        if(object == object_){
            found = true;
        }
    }
    if(found){
        graphikObjekten.removeOne(object_);

    }
}
int Scene::getObjecktSize(){
    return graphikObjekten.size();
}

GraphObjkt* Scene::getObject(int index){
    if(index > 0  && index < graphikObjekten.size())
        return graphikObjekten[index];
}
QVector <GraphObjkt*> Scene::getGraphObjkts() {
    return graphikObjekten;
}

void Scene::mallAllObjectsWidthSameColor(QColor qColor){
    for(int i=0; i<graphikObjekten.size(); i++){
        graphikObjekten[i]->setColor(qColor);
    }
}

