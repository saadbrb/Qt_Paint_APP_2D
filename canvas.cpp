#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QDebug>
#include <vector>
#include <math.h>
#include <cmath>
#include <QPointF>
#include "canvas.h"

// CREAT, DEL, COL, TRAFO


Canvas::Canvas(QWidget *parent)
    : QFrame(parent)
{
    std::cout << "Canvas constructor is called" << std::endl;
    primitiveMode = NONE;
    cellSizeX = width() / GRID_COLS;
    cellSizeY = height() / GRID_ROWS;
}

QSize Canvas::minimumSizeHint() const
{
    return QSize(200,200);
}

QSize Canvas::sizeHint() const
{
    return QSize(640,480);
}
void Canvas::clearCanvas(){

    primitivesScene.removeAllObjects();
    graphObjkt = nullptr;
    clearGrid();
    update();
}


void Canvas::setColor(QColor color){

    qColor = color;
    update();
}
void Canvas::showOnlyOutline(bool outline){

    onlyOutline = outline;
    update();
}
void Canvas::schowAllBBoxes(bool bboxes){

    showAllBboxes = bboxes;
    update();
}

//Diese funktion ist von : NONE, LINE, FREE_HAND, CIRCLE,  RECTANGLE, POLYGON, TRIANGLE, RECHTECKEE

void Canvas::setPrimitiveMode(int mode_){

    primitiveMode = (Canvas::PrimitiveMode) mode_;

    update();
}

//Diese funktion ist von : enum MallenMode { CREAT, DEL, COL, TRAFO };
void Canvas::setMode(MallenMode mode){

    mallenMode = mode;
    update();
}

void Canvas::paintEventCreateDragging(QPainter *painter) {
    if(primitiveMode == LINE){
        graphObjkt = new Line(firstPunkt, lastPunkt, qColor);
        graphObjkt->mallen(painter, showAllBboxes);
        return;
    }
    if (primitiveMode == FREE_HAND) {
        graphObjkt->mallen(painter, showAllBboxes);
        return;
    }
    if (primitiveMode == CIRCLE) {
        graphObjkt = new Circle(firstPunkt, lastPunkt, qColor,onlyOutline);
        graphObjkt->mallen(painter, showAllBboxes);
        return;
    }
    if (primitiveMode == RECTANGLE) {
        graphObjkt = new Rectangle(firstPunkt, lastPunkt, qColor,onlyOutline);
        graphObjkt->mallen(painter, showAllBboxes);
        return;
    }
    if (primitiveMode == POLYGON && graphObjkt == nullptr) {
        // graphObjkt = new Polygone(firstPunkt, lastPunkt, color_mode,only_outline);
        graphObjkt = new Polygone(firstPunkt, lastPunkt, qColor,onlyOutline);
        graphObjkt->mallen(painter, showAllBboxes);
        return;
    }
    if (primitiveMode == POLYGON && graphObjkt != nullptr) {
        graphObjkt->mallen(painter, showAllBboxes);
        return;
    }
    if (primitiveMode == TRIANGLE && graphObjkt == nullptr) {
        std::cout << "TRIANGLE/nullptr firsPunkt: " << firstPunkt.x() << std::endl;
        std::cout << "TRIANGLE/nullptr lastPunkt: " << lastPunkt.x() << std::endl;
        graphObjkt = new Triangle(firstPunkt, lastPunkt, qColor,onlyOutline);
        counterTriangle = counterPresse;
        return;
    }
    if (primitiveMode == TRIANGLE && graphObjkt != nullptr) {
        std::cout << "TRIANGLE/!nullptr firsPunkt: " << graphObjkt->getFirstPunkt().x() << std::endl;
        std::cout << "TRIANGLE/!nullptr lastPunkt: " << graphObjkt->getLastPunkt().x() << std::endl;
        graphObjkt->mallen(painter, showAllBboxes);
        return;
    }
}

void Canvas::paintEventCreate(QPainter *painter) {



    if(dragging){
        paintEventCreateDragging(painter);
        return;
    }
    if (graphObjkt == nullptr){
        return;
    }
    if (primitiveMode != TRIANGLE && primitiveMode != POLYGON) {
        primitivesScene.addObjkt(graphObjkt, showAllBboxes);
        graphObjkt->mallen(painter, showAllBboxes);
        graphObjkt = nullptr;
        return;
    }
    if(primitiveMode == TRIANGLE && (counterPresse == counterTriangle)){
        graphObjkt->addPunkt(lastPunkt);
        graphObjkt->mallen(painter, showAllBboxes);
        return;

    }
    if(primitiveMode == TRIANGLE && (counterPresse > counterTriangle)){
        graphObjkt->addPunkt(lastPunkt);
        primitivesScene.addObjkt(graphObjkt, showAllBboxes);
        graphObjkt->mallen(painter, showAllBboxes);
        graphObjkt = nullptr;
        counterPresse = counterTriangle;
        return;

    }
    if (primitiveMode == POLYGON && !((Polygone *)graphObjkt)->isNear(lastPunkt)) {
        //graphObjkt->mallen(&painter);
        graphObjkt->addPunkt(lastPunkt);
        graphObjkt->mallen(painter, showAllBboxes);
        return;
    }
    if (primitiveMode == POLYGON && ((Polygone *)graphObjkt)->isNear(lastPunkt)) {
        //COde to finich
        graphObjkt->mallen(painter,showAllBboxes);
        //graphObjkt->addPunkt(polyPunkt);
        graphObjkt->mallen(painter, showAllBboxes);
        primitivesScene.addObjkt(graphObjkt, showAllBboxes);
        graphObjkt->mallen(painter, showAllBboxes);
        graphObjkt = nullptr;
        return;
    }
}




void Canvas::gridDeleteCircle(QPointF punkt){
    //TODO

}


void Canvas::paintEvent(QPaintEvent *event) {


    //    static int counter = 0;
    //    counter++;
    //    std::cout << "Canvas paintEvent is called: " << counter << std::endl;
    //    std::cout << "width(): " << width() << std::endl;
    //    std::cout << "width_: " << width_ << std::endl;
    QFrame::paintEvent(event);  // parent class draws border

    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.fillRect(QRectF(0,0, width() -1, height() -1), Qt::white);
    painter.drawRect(QRectF(0,0, width() -1, height() -1));

    std::cout << "painting grid:"<<std::endl;
    for(int i=0; i<GRID_ROWS; i++){
        for(int j=0; j<GRID_COLS; j++){
            grid[i][j].paintAllObjects(&painter, false);
        }
    }
    gridLinesCreate();
    gridLinesScene.paintAllObjects(&painter, showAllBboxes);


    primitivesScene.paintAllObjects(&painter, showAllBboxes);
    if(mallenMode == CREAT){
        paintEventCreate(&painter);
    }
    if (!dragging){
        if (mallenMode == TRAFO){
            moveGridCircle();
            sceneIndex = -1;
        }

        return;
    }

    if(mallenMode == DEL){
        primitivesScene.deleletOneElementIsFound(firstPunkt);
        gridDeleteCircle(firstPunkt);
    }
    else if(mallenMode == COL){
        gridCellColorChanged(firstPunkt);

        primitivesScene.changeColorAndOutline(firstPunkt, qColor, onlyOutline);
    }
    else if (mallenMode == TRAFO) {
        if(firstPunkt == lastPunkt){

            sceneIndex = primitivesScene.isFound(firstPunkt);
            gridCirclesIndex = getGridScene(firstPunkt).isFound(firstPunkt);
            if(gridCirclesIndex != -1){
                tpr = getGridScene(firstPunkt);
                graphObjkt = getGridScene(firstPunkt).getObject(gridCirclesIndex);
                getGridScene(firstPunkt).removeThisObject(graphObjkt);

            }

        }
        if(sceneIndex != -1 || gridCirclesIndex != -1){

            primitivesScene.moveThisObject(sceneIndex, lastPunkt);
            tpr.moveThisObject(0, lastPunkt);
        }
    }


    primitivesScene.paintAllObjects(&painter, showAllBboxes);
    tpr.paintAllObjects(&painter, false);
}

void Canvas::mousePressEvent(QMouseEvent *event) {

    if (event->button() == Qt::LeftButton) {
        dragging = true;


        firstPunkt = event->pos();
        if(primitiveMode == FREE_HAND){
            graphObjkt = new Polyline(firstPunkt, qColor);
        }

        counterPresse++;

        lastPunkt = firstPunkt;


        update();
    }
}
void Canvas::mouseMoveEvent(QMouseEvent *event) {
    if ((event->buttons() & Qt::LeftButton) && dragging) {

        lastPunkt = event->pos();
        if(primitiveMode == FREE_HAND){
            graphObjkt->addPunkt(event->pos());
        }

        update();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event) {

    if (event->button() == Qt::LeftButton && dragging) {
        dragging = false;
        if(primitiveMode == FREE_HAND){
            graphObjkt->addPunkt(event->pos());
        }
        // TODO

        lastPunkt = event->pos();

        update();
    }

}

Scene& Canvas::getGridScene( QPointF p) {

    int col = std::min(int(p.x() / cellSizeX), GRID_COLS - 1) ;
    int row = std::min(int(p.y() / cellSizeY), GRID_ROWS - 1) ;

    gridPositionRows = row;
    gridPositionCols = col;

    std::cout << "cellSizeX: " << cellSizeX << std::endl;
    std::cout << "cellSizeY: " << cellSizeY << std::endl;
    std::cout << "col: " << col << std::endl;
    std::cout << "row: " << row << std::endl;
    return grid[row][col];
}


//void Canvas::fillGrid(QVector<GraphObjkt*> &objBag) {
//    for (int i = 0; i < objBag.size(); i++){
//        QPointF p = objBag[i]->getRefPnt();
//        getGridScene(p).addObjkt(objBag[i], false);
//    }
//    //    int a= frameSize().width();
//    //    QPointF punkt(0.0, 0.0);
//    //    QPointF punkta(0.0, a);

//    //    for(int i=0; i<frameSize().width(); i+=cellSizeX){
//    //        for(int j=0; j<frameSize().height(); j+=cellSizeY){
//    //          //scene.addObjkt((new Line((i,j), (i+cellSizeX,j+cellSizeY)),showAllBboxes);
//    //            //scene.addObjkt(new Line((i,j), (i+cellSizeX,j+cellSizeY)), showAllBboxes);
//    //            QPointF pnktA(i,j);
//    //            QPointF pnktB(i+cellSizeX,j+cellSizeY);
//    //            scene.addObjkt(new Line(pnktA, pnktB, qColor), showAllBboxes);
//    //        }
//    //    }


//    //    for (int i = 0; i < objBag.size(); i++) {
//    //        QPointF p = objBag[i]->getRefPnt();
//    //        std::cout << "p.x():" << p.x() << std::endl;
//    //        std::cout << "p.y():" << p.y() << std::endl;
//    //        int col = p.x() / cellSizeX ;
//    //        int row = p.y() / cellSizeY ;
//    //        if (grid.size() <= row){
//    //            grid.resize(row + 1);
//    //        }
//    //        if (grid[row].size() <= col){
//    //            grid[row].resize(col + 1);
//    //        }
//    //        grid[row][col].push_back(objBag[i]);
//    //    }
//}
void Canvas::clearGrid(){

    for(size_t i=0; i<GRID_ROWS; i++){
        for(size_t j=0; j<GRID_COLS; j++){
            grid[i][j].removeAllObjects();
        }
    }
}


void Canvas::gridLinesCreate(){
    gridLinesScene.removeAllObjects();
    cellSizeX = width() / GRID_COLS;
    cellSizeY = height() / GRID_ROWS;
    for(int i = 1; i < GRID_COLS; ++i){
        double x = i * width() / GRID_COLS;
        QPointF firstPunkt(x, 0.0);
        QPointF lastPunkt(x, height());
        gridLinesScene.addObjkt(new Line(firstPunkt, lastPunkt, constColorGridLines), showAllBboxes);
    }
    for (int i = 1; i < GRID_ROWS; ++i){
        double y = i * height() / GRID_ROWS;
        QPointF firstPunkt(0.0, y);
        QPointF lastPunkt(width(), y);
        gridLinesScene.addObjkt(new Line(firstPunkt, lastPunkt, constColorGridLines), showAllBboxes);
    }

}

void Canvas::gridCellColorChanged(QPointF punkt){

    getGridScene(punkt).mallAllObjectsWidthSameColor(qColor);

}

void Canvas::addNewObjectsToGrid(int generatePoints){

    clearGrid();
    for(unsigned i=0; i<generatePoints; i++){
        double firstPunkt = std::rand() % width();
        double lastPunkt = std::rand() % height();
        QPointF refpunkt(firstPunkt, lastPunkt);
        QPointF lastPunkt_(firstPunkt+6, lastPunkt+6);

        getGridScene(refpunkt).addObjkt((new Circle(refpunkt, lastPunkt_,qColor,false)),false);
    }
    update();
}


void Canvas::moveGridCircle(){

    if(!dragging && gridCirclesIndex != -1 && tpr.getObjecktSize() == 1){
        QPointF punkt = graphObjkt->getRefPnt();
        getGridScene(punkt).addObjkt(graphObjkt, false);
        graphObjkt = nullptr;
        tpr.removeAllObjects();

    }
}

