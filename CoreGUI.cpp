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
    wrapper = new QWidget(&window);
    currentRobotGUI = new RobotGUI(wrapper, &mainWindow, &appConfig);
    return QApplication::exec();
}

void CoreGUI::restartGUI() {
    delete currentRobotGUI;
    currentRobotGUI = new RobotGUI(wrapper, &mainWindow, &appConfig);
}
