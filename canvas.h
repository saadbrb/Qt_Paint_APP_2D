#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QFrame>
#include <QVector>
#include "graphobjkt.h"
#include "line.h"
#include "rectangle.h"
#include "polygone.h"
#include "circle.h"
#include "polyline.h"
#include "triangle.h"
#include "scene.h"


#define GRID_ROWS 6
#define GRID_COLS 8
typedef QVector<GraphObjkt*> Grid[GRID_ROWS][GRID_COLS];
//typedef QVector<QVector<QVector<GraphObjkt*>>> Grid;

class Canvas : public QFrame
{
    Q_OBJECT
public:
    enum PrimitiveMode {
        NONE, LINE, FREE_HAND, CIRCLE,  RECTANGLE, POLYGON, TRIANGLE, RECHTECKEE
    };
    enum MallenMode {
        CREAT, DEL, COL, TRAFO
    };

    explicit Canvas(QWidget *parent = nullptr);
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
    void setPrimitiveMode(int mode_);
    void clearCanvas();
    void setColor(QColor color);
    void showOnlyOutline(bool);
    void schowAllBBoxes(bool);
    void setMode(MallenMode mode);
    void gridLinesCreate();
    void addNewObjectsToGrid(int generatePoints);
    void gridCellColorChanged(GraphObjkt* tpr ,QColor color);
    void gridDeleteCircles();
    void moveGridCircle();
    void fillGrid(QVector<GraphObjkt*> objBag);

protected:
    void paintEvent(QPaintEvent *event) override;
    void paintEventCreateDragging(QPainter *painter);
    void paintEventCreate(QPainter *painter);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    //Scene& getGridScene( QPointF p);
private:
    PrimitiveMode primitiveMode = NONE;
    QColor qColor;
    QColor constColorGridLines = Qt::black;
    MallenMode mallenMode;
    bool onlyOutline = false;
    bool showAllBboxes = false;
    bool dragging = false;
    QPointF firstPunkt, lastPunkt;
    GraphObjkt* graphObjkt = nullptr;
    int counterPresse = 0;
    int counterTriangle;
    double sceneIndex = -1;
    double gridCirclesIndex = -1;
    Grid grid;
    int cellSizeX = 64, cellSizeY = 32;
    Scene primitivesScene;
    Scene gridLinesScene;
    Scene gridCirclesScene;


};

#endif // CANVAS_H





