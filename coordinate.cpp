#include "coordinate.h"
#include "ui_coordinate.h"

coordinate::coordinate(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::coordinate), totalH(350), totalW(700), pointx(40), pointy(320), coorH(totalH - 50),
        coorW(totalW - pointx - 20), segmentationX(10), segmentationY(10) {
    ui->setupUi(this);
    image = QImage(totalW, totalH, QImage::Format_RGB32);  //画布的初始化大小设为600*500，使用32位颜色
    QColor backColor = qRgb(255, 255, 255);    //画布初始化背景色使用白色
    image.fill(backColor);//对画布进行填
}

void coordinate::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawImage(0, 0, image);
}

coordinate::~coordinate() {
    delete ui;
}

void coordinate::setValue(double x, double y) {
    this->Mx = x;
    this->My = y;

}

void coordinate::paint(double x, double y, int n, double summ) {
    setValue(x, y);
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing, true);//设置反锯齿模式，好看一点
    //绘制坐标轴 坐标轴原点(35，280)
    painter.drawRect(5, 5, totalW - 10, totalH - 10);//外围的矩形，从(5,5)起，到(590,290)结束，周围留了5的间隙。
    painter.drawLine(pointx, pointy, coorW + pointx, pointy);//坐标轴x宽度为width
    painter.drawLine(pointx, pointy - coorH, pointx, pointy);//坐标轴y高度为height
    //绘制刻度线
    QPen penDegree;
    penDegree.setColor(Qt::black);
    penDegree.setWidth(2);
    painter.setPen(penDegree);
    double _mxstep = (double) Mx / segmentationX;
    //画上x轴刻度线
    for (int i = 0; i < segmentationX; i++)//分成10份
    {
        //选取合适的坐标，绘制一段长度为4的直线，用于表示刻度
        painter.drawLine(pointx + (i + 1) * coorW / segmentationX, pointy, pointx + (i + 1) * coorW / segmentationX,
                         pointy + 4);
        painter.drawText(pointx + (i + 0.65) * coorW / segmentationX,
                         pointy + 10, QString::number((int) ((i + 1) * _mxstep)));
    }

    //y轴刻度线
    double _myStep = (double) My / 10;//y轴刻度间隔需根据最大值来表示
    for (int i = 0; i < segmentationY; i++) {
        //主要就是确定一个位置，然后画一条短短的直线表示刻度。
        painter.drawLine(pointx, pointy - (i + 1) * coorH / segmentationY,
                         pointx - 4, pointy - (i + 1) * coorH / segmentationY);
        painter.drawText(pointx - 30, pointy - (i + 0.85) * coorH / segmentationY,
                         QString::number((int) (_myStep * (i + 1))));
    }
    QPen pen, penPoint;
    pen.setColor(Qt::black);
    pen.setWidth(2);
    penPoint.setColor(Qt::blue);
    penPoint.setWidth(5);
    //由于y轴是倒着的，所以y轴坐标要pointy-a[i]*ky 其中ky为比例系数
    painter.setPen(pen);//黑色笔用于连线
    painter.drawLine(pointx, pointy - coorH, pointx + coorW, pointy);
    double ky = coorH / 10;
    double kx = coorW / 10;
    for (int i = 0; i < n; i++) {
        painter.setPen(penPoint);//蓝色的笔，用于标记各个点
        double x1 = pointx + kx * i;
        double y1 = pointy - ((int) x - i) * ky;
        painter.drawPoint(x1, y1);
    }
    ui->label->setText("总的和为:  " + QString::number(summ));
}
