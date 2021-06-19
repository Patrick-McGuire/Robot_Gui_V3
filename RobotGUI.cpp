#include <QMainWindow>
#include <QApplication>
#include "RobotGUI.h"
#include <QTimer>
#include "iostream"
#include "WidgetData.h"


RobotGUI::RobotGUI(QWidget *parent, WidgetData *widgetData, TextBoxWidget *textBoxWidget) : QObject(parent) {
    _widgetData = widgetData;
    count = 100;
    count2 = 0;
    _textBoxWidget = textBoxWidget;
    // Timer that calls updateGUI()
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGUI()));
    timer->start(10);
}

void RobotGUI::updateGUI() {
    count += 1;
    count2 -= 0.1;
    _widgetData->setInt("KEY1", count);
    _widgetData->setDouble("KEY2", count2);
    _textBoxWidget->updateData();
}