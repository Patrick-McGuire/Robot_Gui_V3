#include "CoreGUI.h"

CoreGUI::CoreGUI(int argc, char **argv, GuiRunState _runState) : app(argc, argv), window(&mainWindow) {
    // Initialize variables
    runState = _runState;
    wrapper = nullptr;
    currentRobotGUI = nullptr;

    // Data input management
    widgetData = new WidgetData();
    interface = new BaseInterface();
    interface->setWidgetData(widgetData);

    // QT initialization
    mainWindow.setCentralWidget(&window);
    window.show();
    mainWindow.show();

    // Houses configuration data
    appConfig = new AppConfig();
}

int CoreGUI::runGUI() {
    qDebug("Starting GUI\n");

    // Parse the configuration data
    appConfig->parse();
    while(!safeParse() && !quit) {
        appConfig->parse();
    }

    qDebug("............");
    qDebug("Creating window");

    // Create the GUI and start the app
    wrapper = new QWidget(&window);
    currentRobotGUI = new RobotGUI(wrapper, &mainWindow, appConfig, this, windowConfig, widgetData, runState);
    int out = QApplication::exec();

    // Close all the threads
    widgetData->endGui();
    for(auto & thread : threads) {
        thread->join();
    }

    qDebug("............\n");
    qDebug("Closing GUI");
    return out;
}

void CoreGUI::reload() {
    restartGUI();
}

void CoreGUI::openReload() {
    std::string filePath = QFileDialog::getOpenFileName(&mainWindow, "Open XML Configuration File", QString::fromStdString(appConfig->getDefaultXmlPath()), "XML Files (*.xml)").toStdString();
    if(!filePath.empty()) {
        appConfig->setDefaultXmlPath(filePath);
        appConfig->write();
        while(!safeParse() && !quit) {
            appConfig->parse();
        }
        restartGUI();
    }
}

void CoreGUI::reparseReload() {
    while(!safeParse()) {
        appConfig->parse();
    }
    restartGUI();
}

void CoreGUI::restartGUI() {
    qDebug("Closing window");
    qDebug("............\n");
    delete currentRobotGUI;
    delete wrapper;
    qDebug("............");
    qDebug("Creating window");
    wrapper = new QWidget(&window);
    currentRobotGUI = new RobotGUI(wrapper, &mainWindow, appConfig, this, windowConfig, widgetData, runState);
}

bool CoreGUI::safeParse() {
    try {
        windowConfig = XMLInput::parse(getFilePath().c_str());
        return true;
    } catch (...) {
        appConfig->setDefaultXmlPath(APP_CONFIG_NO_XML_PATH);
        appConfig->write();
        return false;
    }
}


std::string CoreGUI::getFilePath() {
    appConfig->parse();
    auto filePath = appConfig->getDefaultXmlPath();
    while (filePath == APP_CONFIG_NO_XML_PATH || !AppConfig::fileExists(filePath)) {
        filePath = QFileDialog::getOpenFileName(&mainWindow, "Open XML Configuration File", QString::fromStdString(appConfig->getDefaultXmlPath()), "XML Files (*.xml)").toStdString();
        if(filePath.empty()) {
            appConfig->setDefaultXmlPath(APP_CONFIG_NO_XML_PATH);
            appConfig->write();
            QApplication::quit();
            quit = true;
            break;
        }
        appConfig->setDefaultXmlPath(filePath);
        appConfig->write();
    }
    return filePath;
}

void CoreGUI::addThreadedInterface(ThreadedInterface *thread) {
    thread->setWidgetData(widgetData);
    thread->startThread();
    threads.push_back(thread);
}


