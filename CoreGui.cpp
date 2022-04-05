#include "CoreGui.h"
#include "Interface/ServerInterface.h"

CoreGui::CoreGui(int argc, char **argv) : app(argc, argv), window(&mainWindow) {
    // Initialize variables
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

int CoreGui::runGUI() {
    qDebug("Starting GUI\n");

    // Parse the configuration data
    appConfig->parse();
    appConfig->load();
    widgetData->setImg(RobotGui::ARROW_ASSET_NAME, appConfig->getAsset(RobotGui::ARROW_ASSET_NAME));
    widgetData->setImg(RobotGui::COMPASS_ASSET_NAME, appConfig->getAsset(RobotGui::COMPASS_ASSET_NAME));
    widgetData->setImg(RobotGui::CROSS_HAIR_ASSET_NAME, appConfig->getAsset(RobotGui::CROSS_HAIR_ASSET_NAME));
    widgetData->setImg(RobotGui::ROLL_DIAL_ASSET_NAME, appConfig->getAsset(RobotGui::ROLL_DIAL_ASSET_NAME));
    widgetData->setImg(RobotGui::ROLL_POINTER_ASSET_NAME, appConfig->getAsset(RobotGui::ROLL_POINTER_ASSET_NAME));
    while(!safeParse() && !quit) {
        appConfig->parse();
    }

    qDebug("............");
    qDebug("Creating window");

    // Create the GUI and start the app
    wrapper = new QWidget(&window);
    currentRobotGUI = new GuiInstance(wrapper, &mainWindow, appConfig, this, windowConfig, widgetData);
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

void CoreGui::reload() {
    restartGUI();
}

void CoreGui::openReload() {
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

void CoreGui::reparseReload() {
    while(!safeParse()) {
        appConfig->parse();
    }
    restartGUI();
}

void CoreGui::restartGUI() {
    qDebug("Closing window");
    qDebug("............\n");
    delete currentRobotGUI;
    delete wrapper;
    qDebug("............");
    qDebug("Creating window");
    wrapper = new QWidget(&window);
    currentRobotGUI = new GuiInstance(wrapper, &mainWindow, appConfig, this, windowConfig, widgetData);
}

bool CoreGui::safeParse() {
    try {
        windowConfig = XMLInput::parse(getFilePath().c_str());
        return true;
    } catch (...) {
        appConfig->setDefaultXmlPath(RobotGui::APP_CONFIG_NO_XML_PATH);
        appConfig->write();
        return false;
    }
}


std::string CoreGui::getFilePath() {
    appConfig->parse();
    auto filePath = appConfig->getDefaultXmlPath();
    while (filePath == RobotGui::APP_CONFIG_NO_XML_PATH || !AppConfig::fileExists(filePath)) {
        filePath = QFileDialog::getOpenFileName(&mainWindow, "Open XML Configuration File", QString::fromStdString(appConfig->getDefaultXmlPath()), "XML Files (*.xml)").toStdString();
        if(filePath.empty()) {
            appConfig->setDefaultXmlPath(RobotGui::APP_CONFIG_NO_XML_PATH);
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

void CoreGui::addThreadedInterface(ThreadedInterface *thread) {
    thread->setWidgetData(widgetData);
    thread->startThread();
    threads.push_back(thread);
}

void CoreGui::addInterface(ServerInterface *serverInterface) {
    serverInterface->setWidgetData(widgetData);
    serverInterface->startServer();
}


