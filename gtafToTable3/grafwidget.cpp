#include "grafwidget.h"

grafWidget::grafWidget(QWidget *parent) :
    QWidget(parent)
{
    //painter=0;
    X_min=0; Y_min=0; X_max=0; Y_max=0;
    x_0=140, y_0=60; //нижний левый угол графика относительно нижнего левого края поля
    x_1=20,  y_1=50;//верхний правый угол графика


    //положение осей в процентах
    x_0_percent=5;
    y_0_percent=5;
    x_1_percent=95;
    y_1_percent=95;

    DX=X_max-X_min; DY=Y_max - Y_min;
    setMinimumSize(300,300);
    painter = new QPainter;
    //qDebug()<<x(X(0))<<y(Y(0));

    x_3=10; y_3=10, r=11; move_k=-1;r0=0; kl_line=0;
    //pointList<<PointXY(10,10)<<PointXY(20,20)<<PointXY(30,30);
    brush_line1 = new QBrush(Qt::blue);
    brush_line1->setStyle(Qt::NoBrush);
    brush_line2 = new QBrush(Qt::blue);
    brush_line2->setStyle(Qt::NoBrush);
    brush_line3 = new QBrush(Qt::blue);
    brush_line3->setStyle(Qt::NoBrush);
    brush_line4 = new QBrush(Qt::blue);
    brush_line4->setStyle(Qt::NoBrush);
    //brush_line->setStyle(Qt::SolidPattern);
//            brush_line->setColor(Qt::green);
    kl_Eraser = 0;
    PointColor = Qt::red;
    LineColor = Qt::blue;
    img.load("2.jpg");
    img_mask = new QImage (img.width(),img.height(),QImage::Format_ARGB32_Premultiplied);
    //img_mask = new QImage (img.width(),img.height(),QImage::Format_Mono);
    //пробую рисовать
//    QPainter painter_maska;
//    painter_maska.begin(img_mask);

//    painter_maska.drawEllipse(100,100,50,60);

//    painter_maska.end();


    pipette_kl=0;
    maska_kl=0;
    maska_kl_eraser=0;
    r_maska = 50;
    rgb_maska = qRgb(255,0,0);
    setMouseTracking(true);

    deltaRGB = 0;
    preview_kl = 0;
}

grafWidget::~grafWidget()
{
    delete painter;
}

void grafWidget::paintEvent(QPaintEvent *)
{
    //painter = new QPainter(this);
    //painter->setRenderHint(QPainter::Antialiasing);
    painter->begin(this);

    w=width(), h=height();

   // QImage img("spectr_lub_YAP.png");
    painter->drawImage(QRect(0,0,w,h),img);
    painter->drawImage(QRect(0,0,w,h),*img_mask);
    limits_graphics();
    if (kl_Eraser==2) Eraser();

    plotingArea();
    plotPoint();
    if(preview_kl!=0) preview();
    if(maska_kl==1 || maska_kl_eraser==1) plot_maska_elipse();

    //painter->drawImage(img_mask);
    //painter_maska.end();
    painter->end();
}

double grafWidget::x(double X) //неправильно
{
    return (X-X_min)/(X_max-X_min)*(w-x_0-x_1)+x_0;
}

double grafWidget::y(double Y) //неправильно
{
    return h-(Y-Y_min)/(Y_max-Y_min)*(h-y_0-y_1)-y_0;
}

double grafWidget::X(double x)
{
    return (x-x_0)*(X_max - X_min)/(x_1-x_0) + X_min;
}

double grafWidget::Y(double y)
{
    //qDebug()<<"Y_min,Y_max,y0,y1,y"<<Y_min<<Y_max<<y_0<<y_1<<y;
    return Y_max-(y-y_0)*(Y_max - Y_min)/(y_1-y_0);
}

QPointF grafWidget::XY_to_xy(QPointF point_XY)
{
    QPointF point;
    point.setX(x(point_XY.x()));
    point.setY(y(point_XY.y()));
    return point;
}

void grafWidget::plotPoint()
{
    for(int i=0;i<pointList_xy.size();i++)
    {
        x_3=pointList_xy[i]->getX(); y_3=pointList_xy[i]->getY();
        //r0=i==move_k ? 1 : 0;
        /*painter->setPen(QPen(Qt::red,2*r+r0));
        painter->drawPoint(x_3,y_3)*/;

        sorting();
        QPolygon plgn;
        for (int j=0;j<pointList_xy.size();j++)
            plgn<<QPoint(pointList_xy[j]->getX(),pointList_xy[j]->getY());
        painter->setPen(QPen(LineColor,2));
        painter->drawPolyline(plgn);
    }
    for(int i=0;i<pointList_xy.size();i++)
    {
        x_3=pointList_xy[i]->getX(); y_3=pointList_xy[i]->getY();
        //соединяю линиями
        painter->setPen(QPen(PointColor,2));
        painter->setBrush(Qt::NoBrush);
        r0=pointList_xy[i]->getR0();
        painter->drawRect(x_3-r/2-r0,y_3-r/2-r0,r+2*r0-1,r+2*r0-1);
        //painter->setPen(QPen(PointColor,2));
        painter->drawPoint(x_3,y_3);
    }
}

void grafWidget::plotingArea() //рисую сетку
{
    double q1=10,q2=40;
    painter->setPen(QPen(Qt::blue,2));
    //x_min
    painter->setBrush(*brush_line1);
    painter->drawLine(x_0,0,x_0,h);
    painter->drawRect(x_0,h/2.*(1.+1./q1),-w/q2,-h/q1);
    //x_max
    painter->setBrush(*brush_line2);
    painter->drawLine(x_1,0,x_1,h);
    painter->drawRect(x_1,h/2.*(1.+1./q1), w/q2,-h/q1);
    //y_min
    painter->setBrush(*brush_line3);
    painter->drawLine(0,y_0,w,y_0);
    painter->drawRect(w/2.*(1.+1./q1),y_0,-w/q1,-h/q2);
    //y_max
    painter->setBrush(*brush_line4);
    painter->drawLine(0,y_1,w,y_1);
    painter->drawRect(w/2.*(1.+1./q1),y_1,-w/q1, h/q2);
}






void grafWidget::save()
{
//        xx=pointList_xy[i].getX(); yy=pointList_xy[i].getY();
//        XX=X(xx); YY=Y(yy);
    double xx, XX, yy, YY;
    QFileDialog *FD=new QFileDialog;
    QString str =FD->getSaveFileName(0,"сохранение файла","./saveFile","*.csv");//qDebug()<<str;
    if (!str.isEmpty()){
        if(!str.endsWith(".csv")) str+=".csv";
        QFile file(str);
        if(file.open(QIODevice::WriteOnly))
        {
            QTextStream strm(&file);
            strm<<str+"\n";
            strm<<"x\t"<<"y\n";
            for(int i=0;i<pointList_xy.size();i++)
            {
                xx=pointList_xy[i]->getX(); yy=pointList_xy[i]->getY();
                XX=X(xx); YY=Y(yy);
                strm<<XX<<"\t"<<YY<<"\n";
            }



            file.close();
        }
    }
}

void grafWidget::setR(int rr)
{
    r=rr*2+1;
    update();
}

void grafWidget::PointColorSlot()
{
    QColor color = QColorDialog::getColor(Qt::red);
    if (color != color.Invalid) PointColor = color;
    update();
}

void grafWidget::LineColorSlot()
{
    QColor color = QColorDialog::getColor(Qt::blue);
    if (color != color.Invalid) LineColor = color;
    update();
}

void grafWidget::loadPic()
{
    QFileDialog *FD = new QFileDialog;
    QString str = FD->getOpenFileName(0,
                                       tr("загрузить картику"),
                                       "Pixmap",
                                       "*.png ;; *.jpg ;; *.bmp");
    if (!str.isEmpty())
        img.load(str);
    delete img_mask;
    img_mask = new QImage (img.width(),img.height(),QImage::Format_ARGB32_Premultiplied);
    //qDebug()<<img.width()<<img.height();
    update();
}

void grafWidget::pipette_slot(bool kl)
{
    pipette_kl = kl;
}


void grafWidget::sorting()
{

    //сортировка влоб
//    PointXY  *pnt;
//    for(int i=0;i<pointList_xy.size();i++)
//    {
//        for(int j=i;j<pointList_xy.size();j++)
//        {
//            if (pointList_xy[j]->getX()<pointList_xy[i]->getX())
//            {
//                pnt=pointList_xy[j];
//                pointList_xy[j]=pointList_xy[i];
//                pointList_xy[i]=pnt;
//            }
//        }
//    }
    //}

    //сортировка вставками
//    template< class T >
//    void insertSort(T* a, int size)
//    {
//        T tmp;
//        for (int i = 1, j; i < size; ++i) // цикл проходов, i - номер прохода
//        {
//            tmp = a[i];
//            for (j = i - 1; j >= 0 && a[j] > tmp; --j) // поиск места элемента в готовой последовательности
//                a[j + 1] = a[j];    // сдвигаем элемент направо, пока не дошли
//            a[j + 1] = tmp; // место найдено, вставить элемент
//        }
//    }

     PointXY *tmp;
        for (int i = 1, j; i < pointList_xy.size(); ++i) // цикл проходов, i - номер прохода
        {
            tmp = pointList_xy[i];
            for (j = i - 1; j >= 0 && pointList_xy[j]->getX() > tmp->getX(); --j) // поиск места элемента в готовой последовательности
                pointList_xy[j + 1] = pointList_xy[j];    // сдвигаем элемент направо, пока не дошли
            pointList_xy[j + 1] = tmp; // место найдено, вставить элемент
        }

}

void grafWidget::plot_maska_elipse()
{
    //double r=50;
    painter->setBrush(QColor(0,0,0,0));
    painter->setPen(QColor(255,0,0,255));
    //double r=50;
    painter->drawEllipse(x_4, y_4, x_5, y_5);
}

void grafWidget::Eraser_slot(bool kl_Eraser_sl)
{
    kl_Eraser = kl_Eraser_sl;
    //qDebug()<<"kl_er"<<kl_Eraser;
}

void grafWidget::avto_gtaf(int n,QRgb rgb)
{
    //шаг в координатах рисунка
    pointList_xy_preview.clear();
    double shag_x=(x_1-x_0)/(n-1)/w*img.width();
    int N_sr;
    double sr;
    QRgb rgbP;
    for(double i=0;i<img.width();i+=shag_x)
    {
        sr=0; N_sr=0;
        for(int j=0;j<img.height();j++)
        {
            //rgb_graf = img.pixel(pe->x()/w*img.width(),pe->y()/h*img.height());
            rgbP=img.pixel(i,j);
            //qDebug()<<rgbP;
            if(fabs(qRed(rgbP)-qRed(rgb))<=deltaRGB && abs(qGreen(rgbP)-qGreen(rgb))<=deltaRGB && abs(qBlue(rgbP)-qBlue(rgb))<=deltaRGB &&  qRed(img_mask->pixel(i,j))!=0)
            {
                //qDebug()<<qRed(img_mask->pixel(i,j))<<qGreen(img_mask->pixel(i,j))<<qBlue(img_mask->pixel(i,j))<<qAlpha(img_mask->pixel(i,j));
                sr+=j;
                N_sr++;
            }
            //qDebug()<<i<<j<<shag_x;

        }
        if(N_sr>0 )
        {sr=sr/N_sr;
            pointList_xy_preview<<new PointXY(i*w/img.width(),sr*h/img.height(),&w,&h);}

        for(int i=0;i<pointList_xy_preview.size();i++)
            pointList_xy_preview[i]->setR0(0);

        update();

    }


}

void grafWidget::maska_slot(bool kl)
{
    maska_kl = kl;
    update();
}

void grafWidget::maska_slot_eraser(bool kl)
{
    maska_kl_eraser = kl;
    update();
}

void grafWidget::set_r_maska(int r)
{
    //qDebug()<<r_maska;
    r_maska = r;
    update();
}

void grafWidget::setDeltaRGB(int delta)
{
    deltaRGB=delta;
}

void grafWidget::set_preview_kl(bool kl)
{
    preview_kl = kl;
}

void grafWidget::add_avto()
{
    for(int i=0;i<pointList_xy_preview.size();i++)
        pointList_xy<<pointList_xy_preview[i];
}


void grafWidget::limits_graphics()
{
    if(x_0_percent<2 || x_0_percent>98) x_0_percent=2;
    if(x_1_percent<2 || x_1_percent>98) x_1_percent=98;
    if(y_0_percent<2 || y_0_percent>98) y_0_percent=2;
    if(y_1_percent<2 || y_1_percent>98) y_1_percent=98;
    x_0=x_0_percent/100.*w;
    y_0=y_0_percent/100.*h;
    x_1=x_1_percent/100.*w;
    y_1=y_1_percent/100.*h;
    //qDebug()<<x_0_percent;
    //qDebug()<<x_0<<y_0<<x_1<<y_1;
}

int grafWidget::in(int xx, int yy, int x0, int y0, int w0, int h0)
{
    if ( (x0-xx)*(x0+w0-xx)<=0 && (y0-yy)*(y0+h0-yy)<=0)
        return 1;
    else
        return 0;
}

void grafWidget::preview()
{

    for(int i=0;i<pointList_xy_preview.size();i++)
    {
        x_3=pointList_xy_preview[i]->getX(); y_3=pointList_xy_preview[i]->getY();
        painter->setPen(QPen(PointColor,5));
        painter->setBrush(Qt::NoBrush);
        painter->drawPoint(x_3,y_3);
        //qDebug()<<"previw"<<x_3<<y_3;
    }
}

void grafWidget::Eraser()
{
    painter->setPen(QPen(Qt::red,1));
    double x,y;
    for(int i=0;i<pointList_xy.size();i++)
        pointList_xy[i]->setR0(0);
    painter->drawRect(QRect(QPoint(x_2,y_2),QPoint(x_3,y_3)));
    for(int i=0;i<pointList_xy.size();i++)
    {
        x=pointList_xy[i]->getX();
        y=pointList_xy[i]->getY();
        if ((x-x_2)*(x-x_3)<=0 && (y-y_2)*(y-y_3)<=0)
            pointList_xy[i]->setR0(-dr0);
    }
}

void grafWidget::set_X_min(double X0)
{
    X_min=X0;
}

void grafWidget::set_Y_min(double Y0)
{
    Y_min=Y0;
}

void grafWidget::set_X_max(double X0)
{
    X_max=X0;
}

void grafWidget::set_Y_max(double Y0)
{
    Y_max=Y0;
}

void grafWidget::mousePressEvent(QMouseEvent * pe)
{
    //    painter->drawLine(x_0,0,x_0,h);
    //    painter->drawRect(x_0,h/2.*(1.+1./q1),-w/q2,-h/q1);
    //    //x_max
    //    painter->drawLine(x_1,0,x_1,h);
    //    painter->drawRect(x_1,h/2.*(1.+1./q1), w/q2,-h/q1);
    //    //y_min
    //    painter->drawLine(0,y_0,w,y_0);
    //    painter->drawRect(w/2.*(1.+1./q1),y_0,-w/q1,-h/q2);
    //    //y_max
    //    painter->drawLine(0,y_1,w,y_1);
    //    painter->drawRect(w/2.*(1.+1./q1),y_1,-w/q1, h/q2);

    //qDebug()<<pipette_kl;

    if (kl_Eraser == 0 && pipette_kl == 0 && maska_kl == 0 && maska_kl_eraser == 0) //включение ластика вырубает остальные средства управления
    {
        if(pe->buttons() & Qt::LeftButton)
        {
            //pointList<<PointXY(pe->x(),pe->y());
            double q1=10,q2=40;
            if  (in(pe->x(),pe->y(),x_0,h/2.*(1.+1./q1),-w/q2,-h/q1)) kl_line=1;
            if  (in(pe->x(),pe->y(),x_1,h/2.*(1.+1./q1), w/q2,-h/q1)) kl_line=2;
            if  (in(pe->x(),pe->y(),w/2.*(1.+1./q1),y_0,-w/q1,-h/q2)) kl_line=3;
            if  (in(pe->x(),pe->y(),w/2.*(1.+1./q1),y_1,-w/q1, h/q2)) kl_line=4;
            x_2=pe->x();
            y_2=pe->y();
        }



        //    painter->drawRect(x_3-r/2-r0,y_3-r/2-r0,r+2*r0-1,r+2*r0-1);
        //    painter->drawPoint(x_3,y_3);
        for(int i=0;i<pointList_xy.size();i++)
        {
            x_3=pointList_xy[i]->getX(); y_3=pointList_xy[i]->getY();
            if(in(pe->x(),pe->y(),x_3-r/2-r0,y_3-r/2-r0,r+2*r0-1,r+2*r0-1))
            {
                if(pe->buttons() & Qt::LeftButton)
                {
                    move_k=i;
                    point_move=pointList_xy[i];
                    pointList_xy[i]->setR0(dr0);
                    x_2=pointList_xy[i]->getX() - pe->x();
                    y_2=pointList_xy[i]->getY() - pe->y();
                }
                if(pe->buttons() & Qt::RightButton)
                {
                    pointList_xy.removeAt(i);
                }
                update();
            }
        }


        if(move_k<0 && kl_line==0)
        {
            if(pe->buttons() & Qt::LeftButton)
            {
                pointList_xy<<new PointXY(pe->x(),pe->y(),&w,&h);
                move_k=pointList_xy.size()-1;
                point_move=pointList_xy[move_k];
                pointList_xy[move_k]->setR0(dr0);
                x_2=0; y_2=0;
                //qDebug()<<move_k;
                update();
            }
        }
    }
    else //если включен ластик
    {
        if(maska_kl==1 || maska_kl_eraser==1) painter_maska.begin(img_mask);

        if(pe->buttons() & Qt::LeftButton)
        {

            if(kl_Eraser!=0)
            {
                x_2=pe->x();
                y_2=pe->y();
                x_3=pe->x();
                y_3=pe->y();
                kl_Eraser=2;
            }
            if(pipette_kl!=0)
            {
                rgb_graf = img.pixel(pe->x()/w*img.width(),pe->y()/h*img.height());
                emit setColor(rgb_graf);
            }
            if(maska_kl==1)
            {
                painter_maska.setCompositionMode(QPainter::CompositionMode_DestinationAtop);
                painter_maska.setBrush(QColor(255,0,0,50));
                painter_maska.setPen(QColor(255,0,0,50));
                //double r_maska=50;
                painter_maska.drawEllipse(pe->x()/w*img_mask->width()-r_maska/2,
                                          pe->y()/h*img_mask->height()-r_maska/2,
                                          r_maska,
                                          r_maska);
                maska_signal();
                update();
            }
            if(maska_kl_eraser==1)
            {
                painter_maska.setCompositionMode(QPainter::CompositionMode_DestinationAtop);
                painter_maska.setBrush(QColor(0,0,0,0));
                painter_maska.setPen(QColor(0,0,0,0));
                //double r_maska=50;
                painter_maska.drawEllipse(pe->x()/w*img_mask->width()-r_maska/2,
                                          pe->y()/h*img_mask->height()-r_maska/2,
                                          r_maska,r_maska);
                maska_signal();
                update();
            }
        }
    }




}



void grafWidget::mouseMoveEvent(QMouseEvent * pe)
{
    //qDebug()<<"!!!!";
    if(pe->buttons() & Qt::LeftButton)
    {
        if (move_k<0)
        {
            if (kl_line==1)
            {
                x_0+=pe->x()-x_2;
                if(x_0<x_1) x_0_percent=x_0/w*100;
                x_2=pe->x();
                brush_line1->setStyle(Qt::SolidPattern);
                update();
            }

            if (kl_line==2)
            {
                x_1+=pe->x()-x_2;
                if(x_0<x_1) x_1_percent=x_1/w*100;
                x_2=pe->x();
                brush_line2->setStyle(Qt::SolidPattern);
                update();
            }

            if (kl_line==3)
            {
                y_0+=pe->y()-y_2;
                if(y_0<y_1) y_0_percent=y_0/h*100;
                y_2=pe->y();
                brush_line3->setStyle(Qt::SolidPattern);
                update();
            }

            if (kl_line==4)
            {
                y_1+=pe->y()-y_2;
                if(y_0<y_1) y_1_percent=y_1/h*100;
                y_2=pe->y();
                brush_line4->setStyle(Qt::SolidPattern);
                update();
            }
        }

        if(move_k>=0)
        {
            if(in(pe->x()+x_2,pe->y()+y_2,0,0,w,h))
                point_move->setXY_percent(pe->x()+x_2,pe->y()+y_2);
            update();
        }

        if (kl_Eraser)
        {
            x_3=pe->x();
            y_3=pe->y();
            update();
        }

        if(pipette_kl!=0)
        {
            rgb_graf = img.pixel(pe->x()/w*img.width(),pe->y()/h*img.height());
            emit setColor(rgb_graf);
        }
        if(maska_kl==1 || maska_kl_eraser==1)
        {
            //double r_maska=50;
            painter_maska.drawEllipse(pe->x()/w*img_mask->width()-r_maska/2,
                                      pe->y()/h*img_mask->height()-r_maska/2,
                                      r_maska,
                                      r_maska);
            maska_signal();
            update();
        }
    }


        if(maska_kl==1 || maska_kl_eraser==1)
        {
            //double r_maska=50;
            x_4 = pe->x()-r_maska/(double)img_mask->width()*w/2;
            y_4 = pe->y()-r_maska/(double)img_mask->height()*h/2;
            x_5 = r_maska/(double)img_mask->width()*w;
            y_5 = r_maska/(double)img_mask->height()*h;
            //qDebug()<<x_4<<y_4<<x_5<<y_5;
            maska_signal();
            update();
        }


}

void grafWidget::mouseReleaseEvent(QMouseEvent * pe)
{
    kl_line=0;
    move_k=-1;

    brush_line1->setStyle(Qt::NoBrush);
    brush_line2->setStyle(Qt::NoBrush);
    brush_line3->setStyle(Qt::NoBrush);
    brush_line4->setStyle(Qt::NoBrush);

        if (kl_Eraser)
        {
            int i=0;
            while(i<pointList_xy.size())
            {
                if (pointList_xy[i]->getR0()==0)
                {
                    i++;
                }
                else
                {
                    pointList_xy.removeAt(i);
                    //qDebug()<<"*";
                }
            }
            kl_Eraser=1;
        }

        if(maska_kl!=0 || maska_kl_eraser!=0)
        {
            painter_maska.end();
            update();
        }


    for(int i=0;i<pointList_xy.size();i++)
        pointList_xy[i]->setR0(0);
    update();
}
