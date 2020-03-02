#include "widget.h"
#include "ui_widget.h"
#include "triangle.h"
#include "QVector"

const int CENTRE = 200;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget() {
    delete ui;
}

void Widget::drawCoordAxes(QPaintEvent *event) {

    Q_UNUSED(event);
    QPainter painter(this);

    painter.setPen(QPen(Qt::red, 1, Qt::SolidLine));

    painter.drawLine(200, 25, 200, 375);
    painter.drawLine(25, 200, 375, 200);

    painter.drawLine(25, 25, 375, 25);
    painter.drawLine(375, 25, 375, 375);
    painter.drawLine(25, 375, 375, 375);
    painter.drawLine(25, 25, 25, 375);

    painter.drawLine(150, 150, 250, 150);
    painter.drawLine(250, 150, 250, 250);
    painter.drawLine(150, 250, 250, 250);
    painter.drawLine(150, 150, 150, 250);

}

void Widget::drawTriangle(QPaintEvent *event, Triangle tr) {

    Q_UNUSED(event);
    QPainter painter(this);

    painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine));
    painter.drawLine(tr.getTop(0), tr.getTop(1));
    painter.drawLine(tr.getTop(0), tr.getTop(2));
    painter.drawLine(tr.getTop(1), tr.getTop(2));

}


void Widget::paintEvent(QPaintEvent *event) {

    drawCoordAxes(event);

    QVector<QPoint>pts;

    QPoint a(220, 150);
    QPoint b(170, 250);
    QPoint c(220, 250);
    pts.push_back(a);
    pts.push_back(b);
    pts.push_back(c);

    Triangle tr(pts);
    drawTriangle(event, tr);

    if (ui->angle->value() != 0) {

        QPoint rPt(ui->coordX->value() + CENTRE, ui->coordY->value() + CENTRE);
        Triangle newTr = tr.rotationAroundPoint(rPt, ui->angle->value());
        drawTriangle(event, newTr);

        Q_UNUSED(event);
        QPainter painter(this);

        painter.setPen(QPen(Qt::black, 5, Qt::SolidLine));
        painter.drawPoint(rPt);

    }

}


void Widget::on_pushButton_clicked()
{
    repaint();
}
