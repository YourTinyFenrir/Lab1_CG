#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "QVector"
#include "QPoint"

class Triangle {
private:
    QVector<QPoint> tops;
public:
    Triangle();
    Triangle(QVector<QPoint>);
    QPoint getTop(int);
    Triangle rotationAroundPoint(QPoint, float);
};

#endif // TRIANGLE_H
