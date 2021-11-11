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

    WindowConfig *testConfig = XMLInput::parse("/home/patrick/Robot_Gui_V3/ExampleXML/Example2.xml");
    tabWidget = new TabWidget(parent, testConfig->firstChild, widgetData);
}

void RobotGUI::updateGUI() {
    tabWidget->updateInFocus();
    _widgetData->resetKeysUpdated();
}

void RobotGUI::mousePress() {

}

void RobotGUI::mouseRelease() {

}

void RobotGUI::mouseMove() {
    std::cout << "HERE!\n";
}
