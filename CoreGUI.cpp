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
}

int CoreGUI::runGUI() {
    qDebug("Starting GUI...");
    qDebug("Creating window");
    wrapper = new QWidget(&window);
    currentRobotGUI = new RobotGUI(wrapper, &mainWindow, &appConfig, this);
    return QApplication::exec();
}

void CoreGUI::restartGUI() {
    qDebug("Closing window\n\n");
    delete currentRobotGUI;
    delete wrapper;
    qDebug("Creating window");
    wrapper = new QWidget(&window);
    currentRobotGUI = new RobotGUI(wrapper, &mainWindow, &appConfig, this);
}
