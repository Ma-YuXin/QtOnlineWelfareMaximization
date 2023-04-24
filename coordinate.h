#ifndef COORDINATE_H
#define COORDINATE_H

#include <QMainWindow>
#include<QPaintEvent>
#include<QtGui>

namespace Ui {
    class coordinate;
}

class coordinate : public QMainWindow {
    Q_OBJECT

public:
    explicit coordinate(QWidget *parent = nullptr);

    void setValue(double x, double y);

    void paint(double, double, int, double);

    ~coordinate();

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::coordinate *ui;
    QImage image;

    int totalW;
    int totalH;
    int pointx, pointy;
    int coorH;
    int coorW; //确定坐标轴宽度跟高度 上文定义画布为600X300，宽高依此而定。
    //确定坐标轴起点坐标，
    int Mx;
    int My;
    int segmentationX;
    int segmentationY;
};

#endif // COORDINATE_H
