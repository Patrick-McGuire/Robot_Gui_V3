#include <QApplication>
#include <QWidget>
#include "iostream"
#include <QMainWindow>
#include "RobotGUI.h"
#include <vector>
#include "WidgetData.h"
#include "Networking/LocalServer.h"
#include <QDesktopWidget>
#include "Constants.h"
#include <QFileDialog>
#include "XML/AppConfig.h"
#include "CoreGUI.h"


int main(int argc, char** argv) {
    auto gui = new CoreGUI(argc, argv);
    return gui->runGUI();
//    // Create the objects needed to run the GUI
//    QApplication app(argc, argv);
//    auto mainWindow = new QMainWindow;
//    auto *win = new QWidget(mainWindow);
//
//    // Get the app configuration data and filepath to xml
//    auto appConfig = new AppConfig;
//
//    // Initialise my objects that run the GUI
//    RobotGUI robotGui(win, mainWindow, appConfig);
//    return QApplication::exec();
}

