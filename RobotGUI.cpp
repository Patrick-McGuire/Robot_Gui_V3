#include <QMainWindow>
#include <QApplication>
#include "RobotGUI.h"
#include <QTimer>
#include "iostream"


RobotGUI::RobotGUI(QWidget *parent) : QObject(parent) {
    // Timer that calls updateGUI()
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGUI()));
    timer->start(10);
}

void RobotGUI::updateGUI() {
}