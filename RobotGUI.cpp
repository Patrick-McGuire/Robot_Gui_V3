#include <QFileDialog>
#include "RobotGUI.h"


RobotGUI::RobotGUI(QWidget *parent, QMainWindow *_mainWindow, AppConfig *_appConfig) : QObject(parent) {
    // Save passed variables
    widgetData = new WidgetData();
    mainWindow = _mainWindow;
    appConfig = _appConfig;

    // Get the app's configuration data
    appConfig->parse();
    auto filePath = appConfig->getDefaultXmlPath();
    if(filePath == appConfigNoXmlPath || !AppConfig::fileExists(filePath)) {
        filePath = QFileDialog::getOpenFileName(mainWindow, "Open XML Configuration File", "/home", "XML Files (*.xml)").toStdString();
        appConfig->setDefaultXmlPath(filePath);
        appConfig->write();
    }

    // Get the window's configuration information
    WindowConfig *testConfig = XMLInput::parse(filePath.c_str());

    // Create the menu bar at the top
    menu = new MenuWidget(mainWindow, appConfig);
    mainWindow->setMenuBar(menu);

    // Create the core widget for the GUI
    coreWidget = GUIMaker::createWidget(parent, testConfig->firstChild, widgetData);

    // Create the server that will update data in the GUI
    server = new LocalServer(parent, widgetData, this);
    server->StartServer();

    // Initialize the window
    mainWindow->setWindowTitle(QString::fromStdString(testConfig->title));
    mainWindow->resize(testConfig->width, testConfig->height);
    mainWindow->setCentralWidget(parent);
    parent->show();
    mainWindow->show();
}

void RobotGUI::updateGUI() {
    coreWidget->updateData(true);
    widgetData->resetKeysUpdated();
}