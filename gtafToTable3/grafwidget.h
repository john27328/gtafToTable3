#ifndef GRAFWIDGET_H
#define GRAFWIDGET_H

#define dr0 2

#include <QWidget>

#include <QPainter>
#include <QPointer>
#include "grafsource.h"
#include <QSize>
#include <QRect>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QDebug>
#include <QDebug>
#include <cmath>
#include <QPolygon>
#include <QPolygonF>
#include <QString>
#include <QLabel>
#include <QPainterPath>
#include <QtGui>
#include <QFile>
#include <QDataStream>
#include <QFileDialog>
#include <QImage>
#include "point.h"
#include <QList>
#include <QPoint>
#include <QPolygon>
#include <QColor>
#include <QColorDialog>
#include <QRgb>
#include <QPalette>

class grafWidget : public QWidget
{
    Q_OBJECT
public:
    explicit grafWidget(QWidget *parent = 0);
    ~grafWidget();
    virtual void paintEvent(QPaintEvent*);
    void addListPoint(grafSource *sourcePTR);
    void clear();

    QString nameX;
    QString nameY;
    QString nameGraf;

private:
    double X_min, X_max, Y_min, Y_max, X_min1, X_max1, Y_min1, Y_max1;
    double x_disp;
    double y_disp;
    double w, h;
    double x_0;
    double y_0;
    double x_1;
    double y_1;
    double x_2;
    double y_2;
    double x_3;
    double y_3;
    double x_4;
    double y_4;
    double x_5;
    double y_5;
    double x_6;
    double y_6;
    double x_7;
    double y_7;
    double x_8;
    double y_8;

    int r, r0;

    double x_0_percent;
    double y_0_percent;
    double x_1_percent;
    double y_1_percent;

    double DX, DY;
    int kl_line;
    double x(double X);
    double y(double Y);
    double X(double x);
    double Y(double y);
    int N_Graf;
    QPointF XY_to_xy(QPointF point_XY);
    int nPoint;
    void extremes();
    void plotPoint();
    void step();
    void plotingArea();
    void plotGraf();
    void plotNames();
    void plotSelection();
    void disp();
    void limits_graphics();
    int in(int xx, int yy, int x0, int y0, int w0, int h0);
    void preview();
    int preview_kl;

    QMouseEvent * ME_pe;

    //void recalculation_of_coordinates_x();
    //void recalculation_of_coordinates_x();
    //void range_XY();
    //void axis();
    //QPainter *painter;
    QPainter *painter;

    //grafSource source;

    QList<grafSource*> grafSourceList;
    QLabel *mouseLabel;

    int move_k;
    QList<PointXY*> pointList_xy;
    QList<PointXY*> pointList_xy_preview;
    QList<PointXY*> pointList_XY;
    int inIMG(int x, int y);
    QBrush *brush_line1;
    QBrush *brush_line2;
    QBrush *brush_line3;
    QBrush *brush_line4;
    int kl_Eraser;
    void Eraser();
    void sorting();
    PointXY *point_move;

    QColor PointColor;
    QColor LineColor;
    QImage img;
    QImage *img_mask;
    QRgb rgb_graf;
    int pipette_kl;
    int maska_kl;
    int maska_kl_eraser;
    QPainter painter_maska;
    void plot_maska_elipse();
    QRgb rgb_maska;


    double r_maska;

    int deltaRGB;

signals:
    void setColor(QRgb rgb);
    void maska_signal();

public slots:
    void set_X_min(double X0);
    void set_Y_min(double Y0);
    void set_X_max(double X0);
    void set_Y_max(double Y0);
    void save();
    void setR(int rr);
    void PointColorSlot();
    void LineColorSlot();
    void loadPic();
    void pipette_slot(bool kl);

    void Eraser_slot(bool kl_Eraser_sl);

    void avto_gtaf(int n, QRgb rgb);//слот формирует превью

    void maska_slot(bool kl);
    void maska_slot_eraser(bool kl);
    void set_r_maska(int r);

    void setDeltaRGB(int delta);
    void set_preview_kl(bool kl);
    void add_avto();


protected:
    virtual void mousePressEvent  (QMouseEvent* pe);
    virtual void mouseReleaseEvent(QMouseEvent* pe);
    virtual void mouseMoveEvent   (QMouseEvent* pe);



};

#endif // GRAFWIDGET_H
