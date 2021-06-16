#include <QMainWindow>
#include <QApplication>
#include "RobotGUI.h"
#include <QTimer>
#include "iostream"


RobotGUI::RobotGUI(QWidget *parent) : QObject(parent) {
    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(updateGUI()));
    timer->start(10);

    countA = 0;
}

void RobotGUI::updateGUI() {
    std::cout << countA;
    countA += 1;
    std::cout << "\n";
}
