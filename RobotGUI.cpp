#include <QMainWindow>
#include <QApplication>
#include "RobotGUI.h"
#include <QTimer>
#include "iostream"
#include "WidgetData.h"
#include <vector>
#include "GUIMaker.h"


RobotGUI::RobotGUI(QWidget *parent, QMainWindow *mainWindow, WidgetData *widgetData, AppConfig *config, const std::string& configPath) : QObject(parent) {
    _widgetData = widgetData;
    _mainWindow = mainWindow;

    WindowConfig *testConfig = XMLInput::parse(configPath.c_str());
    _mainWindow->setWindowTitle(QString::fromStdString(testConfig->title));
    _mainWindow->resize(testConfig->width, testConfig->height);

    layout = new QBoxLayout(QBoxLayout::TopToBottom);
    parent->setLayout(layout);
    menu = new Menu(_mainWindow, config);
    layout->addWidget(menu);
    layout->setMargin(0);
    auto wrap = new QWidget();
    layout->addWidget(wrap, 1);
    tabWidget = new TabWidget(wrap, testConfig->firstChild, widgetData);
}

void RobotGUI::updateGUI() {
    tabWidget->updateInFocus();
    _widgetData->resetKeysUpdated();
}