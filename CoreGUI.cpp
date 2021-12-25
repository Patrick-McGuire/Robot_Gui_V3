#include "CoreGUI.h"

CoreGUI::CoreGUI(int _argc, char **_argv) : app(_argc, _argv), window(&mainWindow) {
    argc = _argc;
    argv = _argv;
    mainWindow.setCentralWidget(&window);
    window.show();
    mainWindow.show();
    appConfig = new AppConfig();
    wrapper = nullptr;
    currentRobotGUI = nullptr;
}

int CoreGUI::runGUI() {
    qDebug("Starting GUI\n");
    appConfig->parse();
    while(!safeParse() && !quit) {
        appConfig->parse();
    }
    qDebug("............");
    qDebug("Creating window");
    wrapper = new QWidget(&window);
    currentRobotGUI = new RobotGUI(wrapper, &mainWindow, appConfig, this, windowConfig);
    std::thread thread1(&CoreGUI::test, this, currentRobotGUI->getWidgetData());

    int out = QApplication::exec();
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
    currentRobotGUI = new RobotGUI(wrapper, &mainWindow, appConfig, this, windowConfig);
}

bool CoreGUI::safeParse() {
    try {
        windowConfig = XMLInput::parse(getFilePath().c_str());
        return true;
    } catch (...) {
        appConfig->setDefaultXmlPath(appConfigNoXmlPath);
        appConfig->write();
        return false;
    }
}


std::string CoreGUI::getFilePath() {
    appConfig->parse();
    auto filePath = appConfig->getDefaultXmlPath();
    while (filePath == appConfigNoXmlPath || !AppConfig::fileExists(filePath)) {
        filePath = QFileDialog::getOpenFileName(&mainWindow, "Open XML Configuration File", QString::fromStdString(appConfig->getDefaultXmlPath()), "XML Files (*.xml)").toStdString();
        if(filePath.empty()) {
            appConfig->setDefaultXmlPath(appConfigNoXmlPath);
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

void CoreGUI::test(WidgetData *widgetData) {
    while (!widgetData->imgExits("asdf")) {
        auto currentKeyType = widgetData->getKeyType("KEY1");
        auto a = widgetData->getJSON("KEY1");
        a->intVal = rand() % 10;
        if(currentKeyType == WidgetData::img_t || currentKeyType == WidgetData::none_t) {
            widgetData->setJSON("KEY1", a);
        } else {
            widgetData->setKeyUpdated("KEY1");
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << "asdf\n";
}

WidgetData *CoreGUI::getWidgetData() {
    return currentRobotGUI->getWidgetData();
}


