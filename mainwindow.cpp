#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow), duration(1000), itemsMargin(53),
          biddersMargin(70), cs(nullptr), v(nullptr), greedy(nullptr), timer(nullptr) {
    ui->setupUi(this);
    group = new QParallelAnimationGroup;
    connect(ui->autoDemoButton, SIGNAL(clicked(bool)), this, SLOT(autoDemo()));
    connect(ui->nextStepButton, SIGNAL(clicked(bool)), this, SLOT(oneStepDemo()));
    connect(ui->inputDataButton, SIGNAL(clicked(bool)), this, SLOT(addItem()));
    connect(ui->inputBiddersButton, SIGNAL(clicked(bool)), this, SLOT(setBidderList()));
    connect(ui->functionButton, SIGNAL(clicked(bool)), this, SLOT(setFunctions()));
    connect(ui->clearButton, SIGNAL(clicked(bool)), this, SLOT(clearData()));
}

void MainWindow::clearData() {
//    std::cout << "clear Data" << std::endl;
    for (int i = 0; i < readyitems.size(); ++i) {
        readyitems[i]->hide();
        delete readyitems[i];
    }
    for (int i = 0; i < displayedItems.size(); ++i) {
        displayedItems[i]->hide();
        delete displayedItems[i];
    }
    for (int i = 0; i < allocatedItems.size(); ++i) {
        allocatedItems[i]->hide();
        delete allocatedItems[i];
    }
    for (int i = 0; i < bidders.size(); ++i) {
        bidders[i]->hide();
        delete bidders[i];
    }
    for (int i = 0; i < biddersTotalLabel.size(); ++i) {
        biddersTotalLabel[i]->hide();
        delete biddersTotalLabel[i];
    }
    for (int i = 0; i < biddersLabel.size(); ++i) {
        biddersLabel[i]->hide();
        delete biddersLabel[i];
    }
    for (int i = 0; i < buttonList.size(); ++i) {
        buttonList[i]->hide();
        delete buttonList[i];
    }
    for (int i = 0; i < funcTypeLabel.size(); ++i) {
        funcTypeLabel[i]->hide();
        delete funcTypeLabel[i];
    }
    readyitems.clear();
    buttonList.clear();
    displayedItems.clear();
    allocatedItems.clear();
    biddersTotalLabel.clear();
    bidders.clear();
    biddersLabel.clear();
    funcTypeLabel.clear();
    delete greedy;
    greedy = nullptr;
}

void MainWindow::setFunctions() {
    QString s = ui->functionTextEdit->text();
    ui->functionTextEdit->setText("");
    char *str = const_cast<char *>( s.toStdString().c_str());
    std::vector<int> f;
    char *pch = strtok(str, " ,.-");
    while (pch != NULL) {
        int tmp = strtol(pch, nullptr, 10);
        f.push_back(tmp);
        pch = strtok(nullptr, " ,.-");
    }
    std::cout << "size : " << f.size() << std::endl;
    if (f.size() != greedy->getN()) {
        while (f.size() < greedy->getN()) {
            f.push_back(1);
        }
        f.resize(greedy->getN());
        ui->infLabel->setText("函数数量和买家数量不等，少的默认用函数1，多的取前n个");
    }
    greedy->initialization(f);
    initFuncLabel();
    std::ostream_iterator<int> os(std::cout, ",");
    std::copy(f.begin(), f.end(), os);
    std::cout << std::endl;
}

void MainWindow::initFuncLabel() {
    for (int i = 0; i < greedy->getN(); ++i) {
        QLabel *ft = new QLabel(ui->itemsList);
        if (greedy->getFuncType(i) == FuncType::CoFunction) {
            ft->setText("覆盖函数");
        } else if (greedy->getFuncType(i) == FuncType::LiFunction) {
            ft->setText("一次函数");
        }
        ft->setGeometry(245, i * biddersMargin + 15, 60, 20);
        ft->setStyleSheet(funcType_SheetStyle);
        ft->show();
        funcTypeLabel.push_back(ft);
    }
}

void MainWindow::setDefaultData() {
    QLabel *label = nullptr;
    for (int i = 0; i < 10; ++i) {
        label = new QLabel(ui->itemsList);
        label->setText(QString::number(i * 10));
        label->setStyleSheet(m_green_SheetStyle);
        label->hide();
        readyitems.push_back(label);
    }
    updateItems();
    greedy = new Greedy<double, double>(5);
    std::vector<int> f;
    srand(time(nullptr));
    for (int i = 0; i < greedy->getN(); ++i) {
        f.push_back(rand() % 2);
    }
    greedy->initialization(f);
    initFuncLabel();
    addbidderLabel(5);
}

void MainWindow::addbidderLabel(int num) {
//    clearData();
    for (int i = 0; i < num; ++i) {
        QLabel *label = new QLabel(ui->itemsList);
        QLabel *la = new QLabel(ui->itemsList);
        QLabel *l = new QLabel(ui->itemsList);
        QPushButton *bt = new QPushButton("详细信息", ui->itemsList);
        label->setText(QString::number(i));
        label->setStyleSheet(bidders_SheetStyle);
        label->setGeometry(300, i * biddersMargin, 30, 30);
        la->setStyleSheet(bidders_label_SheetStyle);
        la->setGeometry(250, i * biddersMargin + 32, 30, 30);
        l->setText("总的边际价值为：" + QString::number(greedy->getTotal(i)));
        l->setStyleSheet(bidders_label_SheetStyle);
        l->setGeometry(250, i * biddersMargin + 45, 30, 30);
        bt->setGeometry(240, i * biddersMargin, 60, 20);
        bt->setStyleSheet(button_SheetStyle);
        la->show();
        label->show();
        l->show();
        bt->show();
        connect(bt, SIGNAL(clicked(bool)), this, SLOT(detail()));
        bidders.push_back(label);
        biddersLabel.push_back(la);
        biddersTotalLabel.push_back(l);
        buttonList.push_back(bt);
    }
}

void MainWindow::setBidderList() {
    QString s = ui->biddersTextEdit->text();
    ui->biddersTextEdit->setValue(0);
    int biddersNum = stoi(s.toStdString());
    greedy = new Greedy<double, double>(biddersNum);
    addbidderLabel(biddersNum);
}

void MainWindow::detail() {
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    int pos = std::find(buttonList.begin(), buttonList.end(), btn) - buttonList.begin();
    FuncType tp = greedy->getFuncType(pos);
    if (tp == FuncType::LiFunction) {
        std::pair < double, double > p = LinearFunction<std::vector < double>, double, double > ::getValue();
        double y = p.second;
        double x = p.second / (-p.first);
        std::cout << "pos: " << pos << " x: " << x << " y: " << y << std::endl;
        if (v) {
            delete v;
            v = nullptr;
        }
        v = new coordinate;
        v->paint(x, y, greedy->getSize(pos), greedy->getTotal(pos));
        v->show();
    } else if (tp == FuncType::CoFunction) {
        std::pair < double, double > p1 = CoverFunction<std::vector < double>, double, double > ::getValue();
        double c = p1.first;
        double tt = p1.second;
        if (cs) {
            delete cs;
            cs = nullptr;
        }
        cs = new coverShow;
        std::vector<double> vec;
        for (int i = 0; i < greedy->getAllocation(pos).size(); ++i) {
            vec.push_back(greedy->getAllocation(pos)[i].getData());
        }
        cs->paint(c, tt, vec, greedy->getTotal(pos));
        cs->show();
    }
}

void MainWindow::addItem() {
    QString s = ui->dataTextEdit->text();
    ui->dataTextEdit->setText("");
    char *str = const_cast<char *>( s.toStdString().c_str());
    char *pch = nullptr;
    QLabel *label = nullptr;
    pch = strtok(str, " ,.-");
    while (pch != NULL) {
        label = new QLabel(ui->itemsList);
        label->setText(QString(QLatin1String(pch)));
        label->setStyleSheet(m_green_SheetStyle);
        label->hide();
        pch = strtok(NULL, " ,.-，。");
        readyitems.push_back(label);
    }
    updateItems();
}

void MainWindow::updateItems() {
    for (int i = displayedItems.size(); i < 10; ++i) {
        if (!readyitems.empty()) {
            QLabel *tmp = readyitems.front();
            tmp->setGeometry(0, i * itemsMargin, 30, 30);
            tmp->show();
            displayedItems.push_back(tmp);
            readyitems.pop_front();
        }
    }
}

void MainWindow::updateLabels(int bid) {
    ui->infLabel->setText("第" + QString::number(greedy->getM()) + "个物品分给" + QString::number(bid) + "号买家");
    for (int i = 0; i < biddersLabel.size(); ++i) {
        biddersLabel[i]->setText("边际效应增量为：" + QString::number(greedy->getMargin(i)));
        biddersTotalLabel[i]->setText("总的边际价值为：" + QString::number(greedy->getTotal(i)));
    }
}

void MainWindow::oneStepDemo() {
    if (displayedItems.empty()) {
//        std::cout << "ijojjlklj" << std::endl;
        ui->infLabel->setText("目前没有物品，请添加物品");
        this->disconnect(timer);
        delete timer;
        timer == nullptr;
        return;
    }
    double value = stod(displayedItems.front()->text().toStdString());
    Item<double> it(value);
    int bid = greedy->fit(it);
    updateLabels(bid);
    group->clear();
    QPropertyAnimation *pAnimation1 = new QPropertyAnimation(displayedItems[0], "geometry");
    pAnimation1->setDuration(duration);
    pAnimation1->setStartValue(QRect(displayedItems[0]->pos().x(), displayedItems[0]->pos().y(), 30, 30));
    pAnimation1->setEndValue(
            QRect(bidders[bid]->pos().x() + greedy->getSize(bid) * 45, bidders[bid]->pos().y(), 30, 30));
    pAnimation1->setEasingCurve(QEasingCurve::Linear);
    group->addAnimation(pAnimation1);
    for (int i = 1; i < displayedItems.size(); ++i) {
        QPropertyAnimation *pAnimation = new QPropertyAnimation(displayedItems[i], "geometry");
        pAnimation->setEasingCurve(QEasingCurve::Linear);
        pAnimation->setDuration(duration);
        pAnimation->setStartValue(QRect(displayedItems[i]->pos().x(), displayedItems[i]->pos().y(), 30, 30));
        pAnimation->setEndValue(QRect(displayedItems[i - 1]->pos().x(), displayedItems[i - 1]->pos().y(), 30, 30));
        group->addAnimation(pAnimation);
    }
    group->start();
    allocatedItems.push_back(displayedItems.front());
    displayedItems.pop_front();
    updateItems();

}

void MainWindow::autoDemo() {
    if (!greedy || greedy->getN() == 0) {
        setDefaultData();
    }
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(oneStepDemo())); // slotCountMessage是我们需要执行的响应函数
    timer->start(duration + 100);
}

MainWindow::~MainWindow() {
    delete ui;
    delete group;
}

