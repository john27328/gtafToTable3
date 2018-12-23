#include "point.h"

PointXY::PointXY()
{
}

PointXY::PointXY(double X0, double Y0, double *w0, double *h0)
{
    w=w0; h=h0;
    X_percent=X0 / *w; Y_percent=Y0 / *h;
    //qDebug()<<*w<<*h;
}

double PointXY::getX()
{
    return X_percent * *w;
}

double PointXY::getY()
{
    return Y_percent * *h;
}

void PointXY::setX_percent(double X0)
{
    X_percent=X0 / *w;
}

void PointXY::setY_percent(double Y0)
{
    Y_percent=Y0 / *h;
}

void PointXY::setXY_percent(double X0, double Y0)
{
    X_percent=X0 / *w;
    Y_percent=Y0 / *h;
}

void PointXY::setR0(int R0)
{
    R=R0;
}

int PointXY::getR0()
{
    return R;
}

int PointXY::getN()
{
    return N;
}

void PointXY::setN(int N0)
{
    N=N0;
}
