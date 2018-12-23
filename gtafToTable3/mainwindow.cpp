#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    double max=99999999;
    HBox=new QHBoxLayout;
    graf=new grafWidget;
    HBox->addWidget(graf,5);
    setLayout(HBox);

    VBox=new QVBoxLayout;
    GrBox=new QGridLayout;

    VBox1 = new QVBoxLayout;
    VBox1->addLayout(GrBox);
    VBox1->addStretch();

    X_min_l=new QLabel("x min");
    X_min_sb=new QDoubleSpinBox;
    X_min_sb->setRange(-max,max);
    GrBox->addWidget(X_min_l,1,0);
    GrBox->addWidget(X_min_sb,1,1);

    X_max_l=new QLabel("x max");
    X_max_sb=new QDoubleSpinBox;
    X_max_sb->setRange(-max,max);
    GrBox->addWidget(X_max_l,2,0);
    GrBox->addWidget(X_max_sb,2,1);

    Y_min_l=new QLabel("y min");
    Y_min_sb=new QDoubleSpinBox;
    Y_min_sb->setRange(-max,max);
    GrBox->addWidget(Y_min_l,3,0);
    GrBox->addWidget(Y_min_sb,3,1);


    Y_max_l=new QLabel("y max");
    Y_max_sb=new QDoubleSpinBox;
    Y_max_sb->setRange(-max,max);
    GrBox->addWidget(Y_max_l,4,0);
    GrBox->addWidget(Y_max_sb,4,1);

    Safe_Button = new QPushButton ("сохранить");
    GrBox->addWidget(Safe_Button,0,1);
    connect(Safe_Button,SIGNAL(clicked()),graf,SLOT(save()));

    Eraser_Button = new QPushButton("ластик");
    Eraser_Button->setCheckable(true);
    Eraser_Button->setChecked(false);
    GrBox->addWidget(Eraser_Button,7,0);

    rPointLBL = new QLabel("размер квадрата");
    GrBox->addWidget(rPointLBL,5,0);

    rPoint = new QSpinBox; rPoint->setRange(0,50);
    rPoint->setValue(5);
    GrBox->addWidget(rPoint,5,1);

    PointColor = new QPushButton("Цвет квадрата");
    GrBox->addWidget(PointColor,6,0);
    LineColor = new QPushButton("цвет линии");
    GrBox->addWidget(LineColor,6,1);

    LoadPic = new QPushButton("загрузить картинку");
    GrBox->addWidget(LoadPic,0,0);

    pipette_pb = new QPushButton("указать цвет графика");
    pipette_color_lbl = new QLabel("цвет графика");
    pipette_pb ->setCheckable(true);
    pipette_pb ->setChecked(false);
    GrBox->addWidget(pipette_pb,9,0);
    GrBox->addWidget(pipette_color_lbl,9,1);

    n_Point_graf_lbl = new QLabel("число точек");
    n_Point_graf_sb = new QSpinBox;
    n_Point_graf_sb->setRange(3,300);
    avto_graf = new QPushButton("построить автоматически");
    GrBox->addWidget(n_Point_graf_lbl,11,0);
    GrBox->addWidget(n_Point_graf_sb,11,1);
    GrBox->addWidget(avto_graf,14,1);
    avto_graf->setDisabled(1);

    //пробую менять цвет

    pal1.setColor(pipette_color_lbl->backgroundRole(),Qt::green);
    pipette_color_lbl->setPalette(pal1);
    pipette_color_lbl->setAutoFillBackground(true);
    //setColor(qRgb(200,200,200));

    maska_graf = new QPushButton("область графика");
    GrBox->addWidget(maska_graf,12,0);
    maska_graf ->setCheckable(true);
    maska_graf ->setChecked(false);

    maska_graf_eraser = new QPushButton("стереть");
    GrBox->addWidget(maska_graf_eraser,12,1);
    maska_graf_eraser ->setCheckable(true);
    maska_graf_eraser ->setChecked(false);

    maska_graf_r_lbl = new QLabel("радиус");
    GrBox->addWidget(maska_graf_r_lbl,13,0);
    maska_graf_r = new QSpinBox; maska_graf_r->setRange(1,500); maska_graf_r->setValue(50);
    GrBox->addWidget(maska_graf_r,13,1);

    deltaRGB_lbl = new QLabel("разброс цвета (0..255)");
    deltaRGB_sb = new QSpinBox; deltaRGB_sb->setRange(0,255);
    GrBox->addWidget(deltaRGB_lbl,10,0);
    GrBox->addWidget(deltaRGB_sb,10,1);

    preview = new QPushButton("предпросмотр");
    preview ->setCheckable(true);
    preview ->setChecked(false);
    GrBox->addWidget(preview,8,0);

    HBox->addLayout(VBox1);


    //graf->show();
    setMinimumSize(900,900);
    connect(X_min_sb,SIGNAL(valueChanged(double)),graf,SLOT(set_X_min(double)));
    connect(Y_min_sb,SIGNAL(valueChanged(double)),graf,SLOT(set_Y_min(double)));
    connect(X_max_sb,SIGNAL(valueChanged(double)),graf,SLOT(set_X_max(double)));
    connect(Y_max_sb,SIGNAL(valueChanged(double)),graf,SLOT(set_Y_max(double)));
    connect(Eraser_Button,SIGNAL(clicked(bool)),graf,SLOT(Eraser_slot(bool)));
    connect(rPoint,SIGNAL(valueChanged(int)),graf,SLOT(setR(int)));
    connect(PointColor,SIGNAL(clicked()),graf,SLOT(PointColorSlot()));
    connect(LineColor,SIGNAL(clicked()),graf,SLOT(LineColorSlot()));
    connect(LoadPic,SIGNAL(clicked()),graf,SLOT(loadPic()));
    connect(pipette_pb,SIGNAL(clicked(bool)),graf,SLOT(pipette_slot(bool)));
    connect(graf, SIGNAL(setColor(QRgb)),this,SLOT(setColor(QRgb)));
    connect(pipette_pb,SIGNAL(clicked(bool)),Eraser_Button,SLOT(setDisabled(bool)));
    connect(Eraser_Button,SIGNAL(clicked(bool)),pipette_pb,SLOT(setDisabled(bool)));
    connect(pipette_pb,SIGNAL(clicked(bool)),maska_graf,SLOT(setDisabled(bool)));
    connect(Eraser_Button,SIGNAL(clicked(bool)),maska_graf,SLOT(setDisabled(bool)));
    connect(this,SIGNAL(auto_graf_signal(int,QRgb)),graf, SLOT(avto_gtaf(int,QRgb)));
    connect(maska_graf,SIGNAL(clicked(bool)),graf,SLOT(maska_slot(bool)));
    connect(maska_graf,SIGNAL(clicked(bool)),Eraser_Button,SLOT(setDisabled(bool)));
    connect(maska_graf,SIGNAL(clicked(bool)),pipette_pb ,SLOT(setDisabled(bool)));
    connect(maska_graf_eraser,SIGNAL(clicked(bool)),Eraser_Button,SLOT(setDisabled(bool)));
    connect(maska_graf_eraser,SIGNAL(clicked(bool)),pipette_pb,SLOT(setDisabled(bool)));
    connect(maska_graf_eraser,SIGNAL(clicked(bool)),maska_graf,SLOT(setDisabled(bool)));
    connect(pipette_pb,SIGNAL(clicked(bool)),maska_graf_eraser,SLOT(setDisabled(bool)));
    connect(Eraser_Button,SIGNAL(clicked(bool)),maska_graf_eraser,SLOT(setDisabled(bool)));
    connect(maska_graf,SIGNAL(clicked(bool)),maska_graf_eraser,SLOT(setDisabled(bool)));

    connect(maska_graf_r,SIGNAL(valueChanged(int)),graf,SLOT(set_r_maska(int)));


    connect(maska_graf_eraser,SIGNAL(clicked(bool)),graf,SLOT(maska_slot_eraser(bool)));

    connect(deltaRGB_sb,SIGNAL(valueChanged(int)),graf,SLOT(setDeltaRGB(int)));

    //connect(avto_graf,SIGNAL(clicked()),this,SLOT(click_avto_graf()));
    connect(preview,SIGNAL(clicked()),this,SLOT(click_avto_graf()));
    connect(preview,SIGNAL(clicked(bool)),graf,SLOT(set_preview_kl(bool)));
    connect(n_Point_graf_sb,SIGNAL(valueChanged(int)),this,SLOT(click_avto_graf()));
    connect(deltaRGB_sb,SIGNAL(valueChanged(int)),this,SLOT(click_avto_graf()));
    connect(graf, SIGNAL(setColor(QRgb)),this,SLOT(click_avto_graf()));
    connect(graf, SIGNAL(maska_signal()),this,SLOT(click_avto_graf()));
    connect(avto_graf,SIGNAL(clicked()),graf,SLOT(add_avto()));
    connect(preview,SIGNAL(clicked(bool)),avto_graf,SLOT(setEnabled(bool)));

}

MainWindow::~MainWindow()
{

}

void MainWindow::click_avto_graf()
{
    if (preview->isChecked()) emit auto_graf_signal(n_Point_graf_sb->value(),rgb_graf);
}

void MainWindow::setColor(QRgb rgb)
{
    rgb_graf = rgb;
    pal1.setColor(pipette_color_lbl->backgroundRole(), rgb);
    pipette_color_lbl->setPalette(pal1);
}

