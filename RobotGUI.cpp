#include <QFileDialog>
#include "RobotGUI.h"
#include <chrono>
#include <thread>

RobotGUI::RobotGUI(QWidget *_parent, QMainWindow *_mainWindow, AppConfig *_appConfig, CoreGUI *_coreGui, const WindowConfig_ptr& _config) : QWidget(_parent) {
    // Save passed variables
    widgetData = new WidgetData();
    mainWindow = _mainWindow;
    appConfig = _appConfig;
    parent = _parent;
    coreGui = _coreGui;
    config = _config;

    // Set up the window
    mainWindow->setWindowTitle(QString::fromStdString(config->title));
    setWindowSize();
    parent->resize(mainWindow->width(), mainWindow->height());

    // Create the menu bar at the top
    menu = new MenuWidget(mainWindow, appConfig, coreGui, this);
    mainWindow->setMenuBar(menu);

    // Create the core widget for the GUI
    config->firstChild->objectName = "1";
    coreWidget = GUIMaker::createWidget(parent, config->firstChild, widgetData);

    // Create the server that will update data in the GUI
    server = new LocalServer(parent, widgetData, this);
    server->StartServer();

    parent->show();

//    parent->setStyleSheet("QWidget#asdfasfd {background-color: rgb(125,125,125)}");
//    this->setStyleSheet(QString("QWidget#") + this->objectName() + "{ background-color: rgb(125,125,125) }");
//    mainWindow->setStyleSheet("QWidget { background-color: rgb(125,125,125) }");
//    coreWidget->updateTheme();
}

void RobotGUI::setWindowSize() {
    int width = config->width == xmlMaxConstID || config->width == xmlAutoConstID ? QApplication::desktop()->availableGeometry().width() : config->width;
    int height = config->height == xmlMaxConstID || config->height == xmlAutoConstID ? QApplication::desktop()->availableGeometry().height() - 50 : config->height;
    mainWindow->resize(width, height);
}

void RobotGUI::updateGUI() {
    coreWidget->updateData(true);
    widgetData->resetKeysUpdated();
}

RobotGUI::~RobotGUI() {
    delete server;
    delete coreWidget;
    delete widgetData;
    delete menu;
}

void RobotGUI::updateTheme(QAction *channelAction) {
    Themes theme = Theme::getThemeFromName(channelAction->data().toString().toStdString());
    coreWidget->updateTheme(theme, true);
}

void RobotGUI::makeWidgetsDraggable() {
    coreWidget->setDraggability(true);
}

void RobotGUI::makeWidgetsFixed() {
    coreWidget->setDraggability(false);
}

