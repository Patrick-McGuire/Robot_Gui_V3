#include <QMainWindow>
#include <QApplication>
#include "RobotGUI.h"
#include <QTimer>
#include "iostream"
#include "WidgetData.h"
#include <vector>
#include "GUIMaker.h"


RobotGUI::RobotGUI(QWidget *parent, WidgetData *widgetData, std::vector<TabInfo*> *config) : QObject(parent) {
    _widgetData = widgetData;
    _config = config;

    guiMaker = new GUIMaker(parent, config, widgetData);
    allWidgets = guiMaker->allWidgets;
}

void RobotGUI::updateGUI() {
    for(int i = 0; i < allWidgets->size(); i++) {
        allWidgets[0][i]->updateData();
    }
}