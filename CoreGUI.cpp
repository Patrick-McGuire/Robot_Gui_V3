//
// Created by patrick on 11/15/21.
//

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
