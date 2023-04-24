#include "covershow.h"
#include "ui_covershow.h"

coverShow::coverShow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::coverShow), totalW(800), totalH(100), coorH(30), coorW(750), pointx(20), pointy(20) {
    ui->setupUi(this);
    image = QImage(totalW, totalH, QImage::Format_RGB32);  //画布的初始化大小设为600*500，使用32位颜色
    QColor backColor = qRgb(255, 255, 255);    //画布初始化背景色使用白色
    image.fill(backColor);//对画布进行填
}

void coverShow::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawImage(0, 0, image);
}


void coverShow::paint(double coverf, double tt, const std::vector<double> &nums, double summ) {
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing, true);//设置反锯齿模式，好看一点
    painter.setPen(Qt::transparent);
    QPen pen; //画笔。绘制图形边线，由颜色、宽度、线风格等参数组成
    pen.setColor(QColor(255, 0, 0, 255));
    QBrush brush;   //画刷。填充几何图形的调色板，由颜色和填充风格组成
    brush.setColor(QColor(237, 145, 33));
    brush.setStyle(Qt::SolidPattern);
    //可在QPaintDevice上绘制各种图形。QPaintDevice有之类QWidget、QImage、QOpenGLPaintDevice等
    painter.setBrush(brush);
    painter.drawRect(pointx, pointy, coorW, coorH);
    brush.setColor(QColor(3, 168, 158));
    painter.setBrush(brush);
//    std::cout<<kc<<" "<<hs<<std::endl;
    for (int i = 0; i < nums.size(); ++i) {
        double num = fmod(nums[i], tt);
        painter.setPen(Qt::transparent);
        double left = num - coverf / 2;
        double li = left < 0 ? 0 : (left / tt) * coorW;
        double right = num + coverf / 2;
        double ri = right > tt ? coorW : (right / tt) * coorW;
        if (left < 0)left = 0;
        if (right > tt)right = tt;
        painter.drawRect(pointx + li, pointy, ri - li, coorH);
        painter.setPen(pen);
        painter.drawText(pointx + li,
                         pointy - 10, QString::number(left));
        painter.drawText(pointx + ri,
                         pointy - 10, QString::number(right));

    }
    //绘制刻度线
    QPen penDegree;
    penDegree.setColor(Qt::black);
    penDegree.setWidth(2);
    painter.setPen(penDegree);
    painter.drawText(pointx,
                     pointy + coorH + 10, QString::number(0));
    painter.drawText(pointx + coorW - 10,
                     pointy + coorH + 10, QString::number(100));
    for (int i = 0; i < 9; i++)//分成10份
    {
        painter.drawText(pointx + (i + 0.9) * coorW / 10,
                         pointy + coorH + 10, QString::number((int) ((i + 1) * 10)));
    }
    ui->label->setText("总的覆盖范围:  " + QString::number(summ));
}

coverShow::~coverShow() {
    delete ui;
}
