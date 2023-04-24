#include "mainwindow.h"
#include"coordinate.h"
#include <QApplication>
#include "greedy.h"
#include <vector>
#include"covershow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
