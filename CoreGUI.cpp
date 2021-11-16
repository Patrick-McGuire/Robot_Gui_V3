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
}

int CoreGUI::runGUI() {
    qDebug("Starting GUI...");
    appConfig->parse();
    windowConfig = XMLInput::parse(getFilePath().c_str());
    qDebug("Creating window");
    wrapper = new QWidget(&window);
    currentRobotGUI = new RobotGUI(wrapper, &mainWindow, appConfig, this, windowConfig);
    return QApplication::exec();
}

void CoreGUI::reload() {
    restartGUI();
}

void CoreGUI::openReload() {
    std::string filePath = QFileDialog::getOpenFileName(&mainWindow, "Open XML Configuration File", "/home", "XML Files (*.xml)").toStdString();
    appConfig->setDefaultXmlPath(filePath);
    appConfig->write();
    windowConfig = XMLInput::parse(getFilePath().c_str());
    restartGUI();
}

void CoreGUI::reparseReload() {
    windowConfig = XMLInput::parse(getFilePath().c_str());
    restartGUI();
}

void CoreGUI::restartGUI() {
    qDebug("Closing window\n\n");
    delete currentRobotGUI;
    delete wrapper;
    qDebug("Creating window");
    wrapper = new QWidget(&window);
    currentRobotGUI = new RobotGUI(wrapper, &mainWindow, appConfig, this, windowConfig);
}

std::string CoreGUI::getFilePath() {
    appConfig->parse();
    auto filePath = appConfig->getDefaultXmlPath();
    while (filePath == appConfigNoXmlPath || !AppConfig::fileExists(filePath)) {
        filePath = QFileDialog::getOpenFileName(&mainWindow, "Open XML Configuration File", "/home", "XML Files (*.xml)").toStdString();
        appConfig->setDefaultXmlPath(filePath);
        appConfig->write();
    }
    return filePath;
}
