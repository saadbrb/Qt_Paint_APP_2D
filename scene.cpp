#include "scene.h"


void Scene::addObjkt(std::shared_ptr<GraphObjkt> objkt, bool showAllBBox){
    //    if(objkt->getSize() >= 2)   {
    graphikObjekten.push_back(std::make_shared<BBoxDecorator>(objkt, showAllBBox));
    std::cout<<"objket added secessful!\n";
    std::cout<<"Size is :  "<<graphikObjekten.size()<<"\n";
    //    }
    //    else {
    //        std::cout<<"Size ist klein! Not added possible!\n";
    //    }
}
void Scene::paintAllObjects(QPainter* event, bool show_all_bboxes){
    for(std::shared_ptr<GraphObjkt> objkt : graphikObjekten){
        objkt->mallen(event, show_all_bboxes);
    }
}

void Scene::deleletOneElementIsFound(QPointF point){
    if(graphikObjekten.size() > 0){
        std::shared_ptr<GraphObjkt> objectToDelete = nullptr;
        for(std::shared_ptr<GraphObjkt> objkt : graphikObjekten){
            if(objkt->isNaehe(point)){
                objectToDelete = objkt;
                break; // Beendet die Schleife, sobald das Objekt gefunden wurde
            }
        }

        // Löscht das gefundene Objekt aus der Liste
        if(objectToDelete != nullptr){
            graphikObjekten.removeOne(objectToDelete);
            std::cout<<"Delete von Element war erfolgreich!\n";
        }
    }
}
std::shared_ptr<GraphObjkt> Scene::changeColorAndOutline(QPointF point, QColor color, bool outline){
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
    if(graphikObjekten.size() > 0 && 0 <= index < graphikObjekten.size()){
        graphikObjekten[index]->bewegen(punkt);
    }
}

void Scene::removeAllObjects(){
    if(graphikObjekten.size() > 0){
        // Leeren Sie den Vektor
        graphikObjekten.clear();
    }
}
void Scene::removeThisObject(std::shared_ptr<GraphObjkt> object_){
    bool found = false;
    for (std::shared_ptr<GraphObjkt> object : graphikObjekten) {
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

std::shared_ptr<GraphObjkt> Scene::getObject(int index){
    if(index > 0  && index < graphikObjekten.size())
        return graphikObjekten[index];
}
QVector <std::shared_ptr<GraphObjkt>> Scene::getGraphObjkts() {
    return graphikObjekten;
}

void Scene::mallAllObjectsWidthSameColor(QColor qColor){
    for(int i=0; i<graphikObjekten.size(); i++){
        graphikObjekten[i]->setColor(qColor);
    }
}

