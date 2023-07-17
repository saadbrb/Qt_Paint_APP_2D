#include <QColorDialog>
#include <QGridLayout>
#include <QDebug>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QDateTime>
#include "canvas.h"
#include "qapplication.h"
#include "paint.h"
#include "ui_paint.h"



Paint::Paint(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Paint)
{

    ui->setupUi(this);

    canvas = new Canvas();
    // Erstellen von Menubar

    QAction *quit = new QAction("&Quit");
    QAction *save = new QAction("Save &Image");
    QMenu *fileMenu = new QMenu("File");
    QMenuBar *menuBar = new QMenuBar();

    fileMenu->addAction(quit);
    fileMenu->addAction(save);
    menuBar->addMenu(fileMenu);
    ui->verticalLayout_4->setMenuBar(menuBar);
    connect(quit, &QAction::triggered, qApp, &QApplication::quit);
    connect(save, &QAction::triggered, this, &Paint::saveImage);

    //Erstellen vom Frame

    ui->verticalLayout_4->replaceWidget(ui->frame, canvas);
    delete ui->frame;
    ui->frame = canvas;
    ui->comboBox->addItem(tr("NoMode"), Canvas::NONE);
    ui->comboBox->addItem(tr("Line"), Canvas::LINE);
    ui->comboBox->addItem(tr("Freehand"), Canvas::FREE_HAND);
    ui->comboBox->addItem(tr("Circle"), Canvas::CIRCLE);
    ui->comboBox->addItem(tr("Rectangle"), Canvas::RECTANGLE);
    ui->comboBox->addItem(tr("Polygon"), Canvas::POLYGON);
    ui->comboBox->addItem(tr("Triangle"), Canvas::TRIANGLE);
    canvas->setMode(Canvas::COL);

}

Paint::~Paint()
{
    delete ui;
}


void Paint::saveImage() {
    // Größe des Viewports ermitteln
    QSize viewportSize = canvas->size();

    // QImage-Objekt erstellen
    QImage image(viewportSize, QImage::Format_RGB32);

    // QPainter-Objekt erstellen, um auf das QImage-Objekt zu zeichnen
    QPainter painter(&image);

    // Den Inhalt des Viewports in das QImage-Objekt zeichnen
    canvas->render(&painter);

    // Automatisch speichern des Bildes
    QString directory = "/home/saad/Bilder/"; // Hier den gewünschten Pfad einsetzen
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss");
    QString fileName = directory + "image_" + timestamp + ".png";
    image.save(fileName);

}

void Paint::primitive_mode_changed()
{

    //    int mode;
    //    mode = ui->comboBox->itemData(
    //                ui->comboBox->currentIndex(), Qt::UserRole). toInt();
    //    viewport->setPrimitiveMode(mode);
    //    qDebug() << "Primitive Mode changed to "<<mode;
}


void Paint::on_setColor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::yellow, this);
    if(color.isValid()){
        qDebug()<<"Color Chooosen : "<<color.name();
        canvas->setColor(color);
    }

}


void Paint::on_clearCanvas_clicked()
{
    canvas->clearCanvas();
    //update();
    qDebug()<<"Clear image called";

}


void Paint::on_comboBox_activated(int mode)
{

    mode = ui->comboBox->itemData(
                ui->comboBox->currentIndex(), Qt::UserRole). toInt();
    canvas->setPrimitiveMode(mode);
    qDebug() << "Primitive Mode changed to "<<mode;
}


void Paint::on_only_outline_clicked(bool checked)
{
    qDebug() << "Only Show Outline :"<<checked;
    canvas->showOnlyOutline(checked);

}


void Paint::on_all_bbox_clicked(bool checked)
{
    qDebug() << "Scow All BBoxes:"<<checked;
    canvas->schowAllBBoxes(checked);
}





void Paint::on_CREAT_clicked()
{
    qDebug() <<"Mode Changed To Creat ";
    canvas->setMode(Canvas::CREAT);
}


void Paint::on_DEL_clicked()
{
    qDebug() <<"Mode Changed To Delete ";
    canvas->setMode(Canvas::DEL);
}


void Paint::on_COL_clicked()
{
    qDebug() <<"Mode Changed To Colore Changed ";
    canvas->setMode(Canvas::COL);
}


void Paint::on_TRAFO_clicked()
{
    qDebug() <<"Mode Changed To Move Object ";
    canvas->setMode(Canvas::TRAFO);
}

int Paint::checkInt(QString number_to_check){
    bool isInt = false;

    // Konvertiere den QString in einen int
    bool ok;
    int intValue = number_to_check.toInt(&ok);

    // Überprüfe, ob die Konvertierung erfolgreich war und der QString eine Ganzzahl ist
    if (ok)
    {
        // Der QString ist eine Ganzzahl
        isInt = true;
        return intValue;
    }
    else
    {
        // Der QString ist keine Ganzzahl
        isInt = false;
        return -1;
    }


}
void Paint::on_generate_points_clicked()
{

    int zahl = checkInt(ui->get_number_punkten->text());
    if(zahl>-1){
        qDebug()<<zahl;
        canvas->addNewObjectsToGrid(zahl);
    }
    else {

        ui->get_number_punkten->setText(QString("Invalide Inpute"));
    }

}

