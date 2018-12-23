#ifndef POINT_H
#define POINT_H

#include <QDebug>

class PointXY
{
public:
    PointXY();
    PointXY(double X0, double Y0, double *w0, double *h0);
    double getX();
    double getY();
    void setX_percent(double X0);
    void setY_percent(double Y0);
    void setXY_percent(double X0, double Y0);
    void setR0(int R0);
    int getR0();
    int getN();
    void setN(int N0);
private:
    double X_percent;
    double Y_percent;
    double R;
    double N;
    double  *w, *h;
};

#endif // POINT_H
