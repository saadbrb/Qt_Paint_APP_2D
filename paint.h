#ifndef PAINT_H
#define PAINT_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Paint; }
QT_END_NAMESPACE

class Canvas;

class Paint : public QWidget
{
    Q_OBJECT

public:
    Paint(QWidget *parent = nullptr);
    ~Paint();


private slots:
    void primitive_mode_changed();

    void on_setColor_clicked();

    void on_clearCanvas_clicked();

    void on_comboBox_activated(int index);

    void on_only_outline_clicked(bool checked);

    void on_all_bbox_clicked(bool checked);


    void on_CREAT_clicked();

    void on_DEL_clicked();

    void on_COL_clicked();

    void on_TRAFO_clicked();

    void saveImage();

    void on_generate_points_clicked();
    int checkInt(QString number_to_check);

private:
    Ui::Paint *ui;
    Canvas* canvas;


};
#endif // PAINT_H
