#include <QMainWindow>
#include <QApplication>
#include "RobotGUI.h"
#include <QTimer>
#include "iostream"
#include "WidgetData.h"
#include <vector>
#include "GUIMaker.h"


RobotGUI::RobotGUI(QWidget *parent, WidgetData *widgetData, WidgetConfig *config, QMainWindow *mainWindow, int width, int height) : QObject(parent) {
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