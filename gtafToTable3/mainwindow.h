#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QDebug>
#include "grafsource.h"
#include "grafwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QPalette>
#include <QRgb>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    QHBoxLayout *HBox;
    QVBoxLayout *VBox;
    QVBoxLayout *VBox1;
    QGridLayout *GrBox;
    QLabel *X_min_l, *Y_min_l, *X_max_l, *Y_max_l;
    QDoubleSpinBox *X_min_sb, *Y_min_sb, *X_max_sb, *Y_max_sb;
    QPushButton *Safe_Button;
    QPushButton *Eraser_Button;
    QLabel *rPointLBL;
    QSpinBox *rPoint;
    QPushButton *PointColor;
    QPushButton *LineColor;
    QPushButton *LoadPic;
    QPushButton *pipette_pb;
    QLabel *pipette_color_lbl;
    QPalette pal1;
    QLabel *n_Point_graf_lbl;
    QSpinBox *n_Point_graf_sb;
    QPushButton *avto_graf;
    QRgb rgb_graf;
    QPushButton *maska_graf;
    QPushButton *maska_graf_eraser;
    QLabel *maska_graf_r_lbl;
    QSpinBox *maska_graf_r;
    QLabel *deltaRGB_lbl;
    QSpinBox *deltaRGB_sb;
    QPushButton *preview;


    grafWidget *graf;

signals:
    void auto_graf_signal(int n, QRgb rgb);

private slots:
    void click_avto_graf();
public slots:
    void setColor(QRgb rgb);

};

#endif // MAINWINDOW_H
