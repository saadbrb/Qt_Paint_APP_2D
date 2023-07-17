#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QDebug>
#include <vector>
#include <math.h>
#include <cmath>
#include <QPointF>
#include <QVector>
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


    //    std::cout << "painting grid:"<<std::endl;
    //    for(int i=0; i<GRID_ROWS; i++){
    //        for(int j=0; j<GRID_COLS; j++){
    //            grid[i][j].paintAllObjects(&painter, false);
    //        }
    //    }
    gridLinesCreate();
    gridLinesScene.paintAllObjects(&painter, showAllBboxes);
    gridCirclesScene.paintAllObjects(&painter, false);
    primitivesScene.paintAllObjects(&painter, showAllBboxes);

    if(mallenMode == CREAT){
        paintEventCreate(&painter);
    }
    if (!dragging){
        if (mallenMode == TRAFO){
            sceneIndex = -1;
            gridCirclesIndex = -1;
            fillGrid(gridCirclesScene.getGraphObjkts());
        }

        return;
    }

    if(mallenMode == DEL){
        primitivesScene.deleletOneElementIsFound(firstPunkt);
        gridCirclesScene.deleletOneElementIsFound(firstPunkt);
    }
    else if(mallenMode == COL){
        primitivesScene.changeColorAndOutline(firstPunkt, qColor, onlyOutline);
        GraphObjkt* tpr = gridCirclesScene.changeColorAndOutline(firstPunkt, qColor, onlyOutline);
        if(tpr != nullptr){
            gridCellColorChanged(tpr, qColor);
        }
    }
    else if (mallenMode == TRAFO) {
        if(firstPunkt == lastPunkt){

            sceneIndex = primitivesScene.isFound(firstPunkt);
            gridCirclesIndex = gridCirclesScene.isFound(firstPunkt);


        }
        if(sceneIndex != -1){
            primitivesScene.moveThisObject(sceneIndex, lastPunkt);
        }
        if( gridCirclesIndex != -1){
            gridCirclesScene.moveThisObject(gridCirclesIndex, lastPunkt);
        }
    }


    primitivesScene.paintAllObjects(&painter, showAllBboxes);
    gridCirclesScene.paintAllObjects(&painter, false);

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
void Canvas::gridDeleteCircles(){

    for(size_t i=0; i<GRID_ROWS; i++){
        for(size_t j=0; j<GRID_COLS; j++){
            grid[i][j].clear();
        }
    }

}

void Canvas::gridCellColorChanged(GraphObjkt* obj, QColor color){

    bool found = false;
    for(size_t i=0; i<GRID_ROWS; i++){
        for(size_t j=0; j<GRID_COLS; j++){
            for(int k=0; k<grid[i][j].size(); k++){
                if(grid[i][j][k]->isNaehe(obj->getRefPnt())){
                    found = true;
                }
            }
            if(found){
                for(int k=0; k<grid[i][j].size(); k++){
                    grid[i][j][k]->setColor(color);
                }
                break;
            }
        }
        if (found) break;
    }
}



void Canvas::addNewObjectsToGrid(int generatePoints){

    gridDeleteCircles();
    gridCirclesScene.removeAllObjects();
    for(unsigned i=0; i < generatePoints; i++){
        double x = std::rand() % width();
        double y = std::rand() % height();
        QPointF refpunkt(x, y);
        QPointF lastPunkt_(x+6, y+6);

        GraphObjkt*  objct = new Circle(refpunkt, lastPunkt_,qColor,false);
        gridCirclesScene.addObjkt(objct,false);
    }
    fillGrid(gridCirclesScene.getGraphObjkts());
    update();
}

void Canvas::fillGrid(QVector<GraphObjkt*> objBag) {
    gridDeleteCircles();
    for (int i = 0; i < objBag.size(); i++){
        QPointF p = objBag[i]->getRefPnt();

        int col = std::min(GRID_COLS - 1, int(std::floor(p.x() / cellSizeX)));
        int row = std::min(GRID_ROWS - 1, int(std::floor(p.y() / cellSizeY)));

        // Überprüfe, ob Zeilen- und Spaltenindizes gültig sind
        //        if (row >= 0 && row < GRID_ROWS && col >= 0 && col < GRID_COLS) {
        grid[row][col].push_back(objBag[i]);
        //        } else {
        //            std::cerr << "Ungültiger Index: (" << row << ", " << col << ")\n";
        //        }
    }


}



void Canvas::moveGridCircle(){


}

//Scene& Canvas::getGridScene( QPointF p) {

//    int col = std::min(int(p.x() / cellSizeX), GRID_COLS - 1) ;
//    int row = std::min(int(p.y() / cellSizeY), GRID_ROWS - 1) ;

//    gridPositionRows = row;
//    gridPositionCols = col;

//    std::cout << "cellSizeX: " << cellSizeX << std::endl;
//    std::cout << "cellSizeY: " << cellSizeY << std::endl;
//    std::cout << "col: " << col << std::endl;
//    std::cout << "row: " << row << std::endl;
//    return grid[row][col];
//}
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


