#ifndef COVERSHOW_H
#define COVERSHOW_H

#include <QMainWindow>
#include<QPaintEvent>
#include<QtGui>
#include<iostream>

namespace Ui {
    class coverShow;
}

class coverShow : public QMainWindow {
    Q_OBJECT

public:
    explicit coverShow(QWidget *parent = nullptr);

    ~coverShow();

    void paint(double, double, const std::vector<double> &, double);

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::coverShow *ui;
    QImage image;
    double totalW, totalH;
    int coorH;
    int coorW;
    int pointx, pointy;
};

#endif // COVERSHOW_H
