#include <QFileDialog>
#include "RobotGUI.h"
#include <chrono>
#include <thread>

RobotGUI::RobotGUI(QWidget *_parent, QMainWindow *_mainWindow, AppConfig *_appConfig, CoreGUI *_coreGui) : QWidget(_parent) {
    // Save passed variables
    widgetData = new WidgetData();
    mainWindow = _mainWindow;
    appConfig = _appConfig;
    parent = _parent;
    coreGui = _coreGui;

    // Get the app's configuration data
    appConfig->parse();
    auto filePath = appConfig->getDefaultXmlPath();
    if(filePath == appConfigNoXmlPath || !AppConfig::fileExists(filePath)) {
        filePath = QFileDialog::getOpenFileName(mainWindow, "Open XML Configuration File", "/home", "XML Files (*.xml)").toStdString();
        appConfig->setDefaultXmlPath(filePath);
        appConfig->write();
    }

    // Get the window's configuration information
    WindowConfig_ptr testConfig = XMLInput::parse(filePath.c_str());

    // Create the menu bar at the top
    menu = new MenuWidget(mainWindow, appConfig, coreGui);
    mainWindow->setMenuBar(menu);

    // Create the core widget for the GUI
    coreWidget = GUIMaker::createWidget(parent, testConfig->firstChild, widgetData);

    // Create the server that will update data in the GUI
    server = new LocalServer(parent, widgetData, this);
    server->StartServer();

    // Set up the window
    mainWindow->setWindowTitle(QString::fromStdString(testConfig->title));
    mainWindow->resize(testConfig->width, testConfig->height);
    parent->resize(testConfig->width, testConfig->height);
    parent->show();
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
