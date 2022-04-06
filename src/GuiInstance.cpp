#include <QFileDialog>
#include "GuiInstance.h"
#include <thread>
#include "../lib/CommonFunctions.h"
#include "WidgetData.h"


GuiInstance::GuiInstance(QWidget *_parent, QMainWindow *_mainWindow, AppConfig *_appConfig, RobotGui::GuiCore *_coreGui, const RobotGui::WindowConfig_ptr &_config, RobotGui::WidgetData *_widgetData)
        : QWidget(_parent) {
    // Save passed variables
    widgetData = _widgetData;
    mainWindow = _mainWindow;
    appConfig = _appConfig;
    parent = _parent;
    coreGui = _coreGui;
    config = _config;

    if (config->updateRate <= 0) {
        timerUpdateTime = 33;
    } else {
        timerUpdateTime = 1000 / config->updateRate;
    }

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

    //Hardcoded settings tab for first tab widget
    if (true == 4) { //Change this to not always true when you want to switch the settings tab on and off
        auto settingsTabConfig = std::make_shared<RobotGui::WidgetConfig>();
        settingsTabConfig->type = RobotGui::SETTINGS_TAB_STRID;
        settingsTabConfig->backgroundColor = RobotGui::Xml::THEME_CONST;
        settingsTabConfig->textColor = RobotGui::Xml::THEME_CONST;
        settingsTabConfig->headerColor = RobotGui::Xml::THEME_CONST;
        settingsTabConfig->relief = RobotGui::Xml::THEME_CONST;
        settingsTabConfig->font = RobotGui::Xml::THEME_CONST;
        settingsTabConfig->borderColor = RobotGui::Xml::THEME_CONST;

        std::vector<std::shared_ptr<RobotGui::WidgetConfig>> tabWidgetConfig;
        tabWidgetConfig.push_back(settingsTabConfig);
        config->firstChild->tabNames.insert(config->firstChild->tabNames.begin(), "Settings");
        config->firstChild->tabWidgets.insert(config->firstChild->tabWidgets.begin(), tabWidgetConfig);
    }

    // Create the core widget for the GUI
    config->firstChild->objectName = "1";
    coreWidget = GUIMaker::createWidget(parent, config->firstChild, widgetData, theme);


    qDebug("Starting update timer");
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGUI()));
    timer->start(timerUpdateTime);


    parent->show();
    setTheme();
}

void GuiInstance::setWindowSize() {
    int width = config->width == RobotGui::Xml::MAX_CONST_ID || config->width == RobotGui::Xml::AUTO_CONST_ID ? QApplication::desktop()->screenGeometry().width() : config->width;
    int height = config->height == RobotGui::Xml::MAX_CONST_ID || config->height == RobotGui::Xml::AUTO_CONST_ID ? QApplication::desktop()->screenGeometry().height() - 50 : config->height;
    mainWindow->resize(width, height);
}

void GuiInstance::updateGUI() {
    coreWidget->updateData(true);
    widgetData->resetKeysUpdated();
}

GuiInstance::~GuiInstance() {
    delete coreWidget;
    delete menu;
    delete theme;
}

void GuiInstance::updateTheme(QAction *channelAction) {
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

RobotGui::WidgetData *GuiInstance::getWidgetData() {
    return widgetData;
}

void GuiInstance::save() {
    return;
    XMLOutput::output(appConfig->getDefaultXmlPath().c_str(), config, coreWidget);
}

void GuiInstance::saveAs() {
    std::string filePath = QFileDialog::getSaveFileName(mainWindow, "Save as", QString::fromStdString(appConfig->getDefaultXmlPath()), "XML Files (*.xml)").toStdString();
    if (!filePath.empty()) {
        appConfig->setDefaultXmlPath(filePath);
        appConfig->write();
        XMLOutput::output(filePath.c_str(), config, coreWidget);
    }
}

