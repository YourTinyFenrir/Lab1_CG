#include "triangle.h"
#include "QVector3D"
#include "qmath.h"

Triangle::Triangle() {

    QPoint pt(0, 0);

    for (int i = 0; i < 3; ++i)
        tops.push_back(pt);

}

Triangle::Triangle(QVector<QPoint> pts) {
    tops = pts;
}

QPoint Triangle::getTop(int num) {
    if (num < 3)
        return tops[num];
    else
        throw "Выбран неверный номер вершины";
}

QVector<QVector3D> multiply3DMatrix(QVector<QVector3D> first, QVector<QVector3D> second) {

    QVector<QVector3D> result(3);

    for (int i = 0; i < first.size(); ++i) {

        float temp = first[i].x() * second[0].x() + first[i].y() * second[1].x() + first[i].z() * second[2].x();
        result[i].setX(temp);
        temp = first[i].x() * second[0].y() + first[i].y() * second[1].y() + first[i].z() * second[2].y();
        result[i].setY(temp);
        temp = first[i].x() * second[0].z() + first[i].y() * second[1].z() + first[i].z() * second[2].z();
        result[i].setZ(temp);

    }

    return result;

}

Triangle Triangle::rotationAroundPoint(QPoint pt, float angle) {

    QVector<QVector3D> baseTr;

    for(int i = 0; i < tops.size(); ++i)
        baseTr.push_back(QVector3D(tops[i].x(), tops[i].y(), 1));

    QVector<QVector3D> unitMatrix;

    QVector3D temp0(1,0,0); unitMatrix.push_back(temp0);
    QVector3D temp1(0,1,0); unitMatrix.push_back(temp1);
    QVector3D temp2(0,0,1); unitMatrix.push_back(temp2);

    QVector<QVector3D> centreDisplaceMatrix(unitMatrix);
    temp2.setX(-pt.x());
    temp2.setY(-pt.y());
    centreDisplaceMatrix[2] = temp2;

    QVector<QVector3D> rotationMatrix(unitMatrix);
    float radAngle = qDegreesToRadians(angle);
    temp0.setX(qCos(radAngle));
    temp0.setY(qSin(radAngle));
    temp1.setX(-qSin(radAngle));
    temp1.setY(qCos(radAngle));
    rotationMatrix[0] = temp0;
    rotationMatrix[1] = temp1;

    QVector<QVector3D> returnBaseCoordMatrix(unitMatrix);
    temp2.setX(pt.x());
    temp2.setY(pt.y());
    returnBaseCoordMatrix[2] = temp2;

    baseTr = multiply3DMatrix(baseTr, centreDisplaceMatrix);
    baseTr = multiply3DMatrix(baseTr, rotationMatrix);
    baseTr = multiply3DMatrix(baseTr, returnBaseCoordMatrix);

    QVector<QPoint> tempPts;
    QPoint tempPt;
    tempPt.setX(baseTr[0].x()); tempPt.setY(baseTr[0].y());
    tempPts.push_back(tempPt);
    tempPt.setX(baseTr[1].x()); tempPt.setY(baseTr[1].y());
    tempPts.push_back(tempPt);
    tempPt.setX(baseTr[2].x()); tempPt.setY(baseTr[2].y());
    tempPts.push_back(tempPt);

    Triangle tr(tempPts);

    return tr;

}
