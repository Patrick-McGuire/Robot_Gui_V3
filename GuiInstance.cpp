#include <QFileDialog>
#include "GuiInstance.h"
#include <thread>
#include "CommonFunctions.h"


GuiInstance::GuiInstance(QWidget *_parent, QMainWindow *_mainWindow, AppConfig *_appConfig, CoreGui *_coreGui, const RobotGui::WindowConfig_ptr& _config, WidgetData *_widgetData, RobotGui::GuiRunState _runState) : QWidget(_parent) {
    // Save passed variables
    runState = _runState;
    widgetData = _widgetData;//new WidgetData();
    mainWindow = _mainWindow;
    appConfig = _appConfig;
    parent = _parent;
    coreGui = _coreGui;
    config = _config;

    theme = new Theme(config->theme);

    // Set up the window
    mainWindow->setWindowTitle(QString::fromStdString(config->title));
    mainWindow->setObjectName("mainWindow");
    setWindowSize();
    parent->resize(mainWindow->width(), mainWindow->height());

    // Create the menu bar at the top
    menu = new MenuWidget(mainWindow, appConfig, coreGui, this, theme);
    mainWindow->setMenuBar(menu);
    mainWindow->menuBar()->setObjectName("menuBar");
    mainWindow->menuWidget()->setObjectName("menuWidget");

    // Create the core widget for the GUI
    config->firstChild->objectName = "1";
    coreWidget = GUIMaker::createWidget(parent, config->firstChild, widgetData, theme);

    // Create the server that will update data in the GUI
    if(runState == RobotGui::UPDATE_ON_POST || runState == RobotGui::UPDATE_PERIODIC_AND_ON_POST) {
        server = new LocalServer(parent, widgetData, this);
        server->StartServer();
    }

    // Create a timer to update the GUI
    if(runState == RobotGui::UPDATE_PERIODIC || runState == RobotGui::UPDATE_PERIODIC_AND_ON_POST) {
        qDebug("Starting update timer");
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(updateGUI()));
        timer->start(timerUpdateTime);
    }

    parent->show();
    setTheme();
}

void GuiInstance::setWindowSize() {
    int width = config->width == RobotGui::Xml::MAX_CONST_ID || config->width == RobotGui::Xml::AUTO_CONST_ID ? QApplication::desktop()->availableGeometry().width() : config->width;
    int height = config->height == RobotGui::Xml::MAX_CONST_ID || config->height == RobotGui::Xml::AUTO_CONST_ID ? QApplication::desktop()->availableGeometry().height() - 50 : config->height;
    mainWindow->resize(width, height);
}

void GuiInstance::updateGUI() {
    coreWidget->updateData(true);
    widgetData->resetKeysUpdated();
}

GuiInstance::~GuiInstance() {
    delete server;
    delete coreWidget;
    delete menu;
    delete theme;
}

void GuiInstance::updateTheme(QAction *channelAction) {
    theme->setTheme(channelAction->data().toString().toStdString());
    config->theme = Theme::getThemeName(theme->getTheme());
    setTheme();
}

void GuiInstance::forceTheme(QAction *channelAction) {
    theme->setTheme(channelAction->data().toString().toStdString());
    config->theme = Theme::getThemeName(theme->getTheme());
    setTheme();
}


void GuiInstance::makeWidgetsDraggable() {
    coreWidget->setDraggability(true);
}

void GuiInstance::makeWidgetsFixed() {
    coreWidget->setDraggability(false);
}

void GuiInstance::setTheme() {
    std::string darker_color = CommonFunctions::GenerateDarkerColor(theme->getBackgroundColor(), 10);
    mainWindow->setStyleSheet("QWidget#mainWindow { background-color: " + QString::fromStdString(darker_color) + "}");
    menu->updateTheme();
    coreWidget->updateStyle();
}

WidgetData *GuiInstance::getWidgetData() {
    return widgetData;
}

void GuiInstance::save() {
    // "/home/patrick/Robot_Gui_V3/ExampleXML/TestWrite.xml"
    XMLOutput::output(appConfig->getDefaultXmlPath().c_str(), config, coreWidget);
}

void GuiInstance::saveAs() {
    std::string filePath = QFileDialog::getSaveFileName(mainWindow, "Save as", QString::fromStdString(appConfig->getDefaultXmlPath()), "XML Files (*.xml)").toStdString();
    if(!filePath.empty()) {
        appConfig->setDefaultXmlPath(filePath);
        appConfig->write();
        XMLOutput::output(filePath.c_str(), config, coreWidget);
    }
}

