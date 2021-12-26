#include <QFileDialog>
#include "RobotGUI.h"
#include <thread>
#include "CommonFunctions.h"


RobotGUI::RobotGUI(QWidget *_parent, QMainWindow *_mainWindow, AppConfig *_appConfig, CoreGUI *_coreGui, const WindowConfig_ptr &_config, WidgetData *_widgetData, GuiRunState _runState) : QWidget(_parent) {
    // Save passed variables
    runState = _runState;
    widgetData = _widgetData;//new WidgetData();
    mainWindow = _mainWindow;
    appConfig = _appConfig;
    parent = _parent;
    coreGui = _coreGui;
    config = _config;

    // Set up the window
    mainWindow->setWindowTitle(QString::fromStdString(config->title));
    mainWindow->setObjectName("mainWindow");
    setWindowSize();
    parent->resize(mainWindow->width(), mainWindow->height());

    // Create the menu bar at the top
    menu = new MenuWidget(mainWindow, appConfig, coreGui, this);
    mainWindow->setMenuBar(menu);
    mainWindow->menuBar()->setObjectName("menuBar");
    mainWindow->menuWidget()->setObjectName("menuWidget");

    // Create the core widget for the GUI
    config->firstChild->objectName = "1";
    coreWidget = GUIMaker::createWidget(parent, config->firstChild, widgetData);

    // Create the server that will update data in the GUI
    if (runState == updateOnPost || runState == updatePeriodicOnPost) {
        server = new LocalServer(parent, widgetData, this);
        server->StartServer();
    }

    // Create a timer to update the GUI
    if (runState == updatePeriodic || runState == updatePeriodicOnPost) {
        qDebug("Starting update timer");
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(updateGUI()));
        timer->start(timerUpdateTime);
    }

    parent->show();

    setTheme(Theme::getThemeFromName(config->theme), false);
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
    delete menu;
}

void RobotGUI::updateTheme(QAction *channelAction) {
    Themes theme = Theme::getThemeFromName(channelAction->data().toString().toStdString());
    setTheme(theme, false);
}

void RobotGUI::forceTheme(QAction *channelAction) {
    Themes theme = Theme::getThemeFromName(channelAction->data().toString().toStdString());
    setTheme(theme, true);
}


void RobotGUI::makeWidgetsDraggable() {
    coreWidget->setDraggability(true);
}

void RobotGUI::makeWidgetsFixed() {
    coreWidget->setDraggability(false);
}

void RobotGUI::setTheme(Themes _theme, bool force) {
    std::string darker_color = CommonFunctions::GenerateDarkerColor(Theme::getBackgroundColorStr(_theme), 10);
    mainWindow->setStyleSheet("QWidget#mainWindow { background-color: " + QString::fromStdString(darker_color) + "}");
    menu->updateTheme(_theme);
    coreWidget->updateStyle(_theme, force);
}

WidgetData *RobotGUI::getWidgetData() {
    return widgetData;
}

