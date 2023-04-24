#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include<QApplication>
#include<iostream>
#include<QLabel>
#include"styleSheet.h"
#include<iostream>
#include <QPropertyAnimation>
#include<list>
#include<QLayout>
#include<vector>
#include<deque>
#include<QParallelAnimationGroup>
#include<unistd.h>
#include<stdio.h>
#include<QTimer>
#include<QEventLoop>
#include"greedy.h"
#include<string>
#include"coordinate.h"
#include"covershow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QParallelAnimationGroup *group;
    std::deque<QLabel *> readyitems;
    std::deque<QLabel *> displayedItems;
    std::deque<QLabel *> allocatedItems;
    std::vector<QLabel *> bidders;
    std::vector<QLabel *> biddersLabel;
    std::vector<QLabel *> biddersTotalLabel;
    std::vector<QLabel *> funcTypeLabel;
    std::vector<QPushButton *> buttonList;
    coordinate *v;
    coverShow *cs;
    Greedy<double, double> *greedy;
    QTimer *timer;
    int itemsMargin;
    int biddersMargin;
    unsigned int duration;

    void addbidderLabel(int);

    void updateItems();

    void updateLabels(int);

    void setDefaultData();

    void initFuncLabel();

private
    slots:
            void detail();

    void clearData();

    void addItem();

    void autoDemo();

    void setBidderList();

    void oneStepDemo();

    void setFunctions();
};
#endif // MAINWINDOW_H
