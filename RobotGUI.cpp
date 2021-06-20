#include <QMainWindow>
#include <QApplication>
#include "RobotGUI.h"
#include <QTimer>
#include "iostream"
#include "WidgetData.h"
#include <vector>
#include "GUIMaker.h"
#include <QMainWindow>

RobotGUI::RobotGUI(QWidget *parent, WidgetData *widgetData, std::vector<TabInfo*> *config, QMainWindow *mainWindow, int width, int height) : QObject(parent) {
    _widgetData = widgetData;
    _config = config;
    _height = height;
    _width = width;
    _mainWindow = mainWindow;

//    connect(_mainWindow, &QMainWindow::mousePress , this, SLOT(mouseMove()));

    guiMaker = new GUIMaker(parent, config, widgetData, width, height);
    allWidgets = guiMaker->allWidgets;
}

void RobotGUI::updateGUI() {
    for(int i = 0; i < allWidgets->size(); i++) {
        allWidgets[0][i]->updateData();
    }
}

void RobotGUI::mousePress() {

}

void RobotGUI::mouseRelease() {

}

void RobotGUI::mouseMove() {
    std::cout << "HERE!\n";
}
