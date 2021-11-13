#include <QApplication>
#include <QWidget>
#include "iostream"
#include <QMainWindow>
#include "RobotGUI.h"
#include <vector>
#include "WidgetData.h"
#include "Networking/LocalServer.h"
#include <QRect>
#include <QDesktopWidget>
#include "Constants.h"


#include "experimental/filesystem"
#include <iostream>
#include <fstream>

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <QFileDialog>
#include "XML/AppConfig.h"


int main(int argc, char** argv) {
    // Create the objects needed to run the GUI
    auto widgetData = new WidgetData();
    QApplication app(argc, argv);
    auto mainWindow = new QMainWindow;
    auto *win = new QWidget(mainWindow);

    // Get the app configuration data and filepath to xml
    auto appConfig = new AppConfig;
    appConfig->parse();
    auto filePath = appConfig->getDefaultXmlPath();
    if(filePath == appConfigNoXmlPath || !AppConfig::fileExists(filePath)) {
        filePath = QFileDialog::getOpenFileName(mainWindow, "Open XML Configuration File", "/home", "XML Files (*.xml)").toStdString();
        appConfig->setDefaultXmlPath(filePath);
        appConfig->write();
    }

    // Initialise my objects that run the GUI
    RobotGUI robotGui(win, mainWindow, widgetData, appConfig, filePath);
    LocalServer Server(win, widgetData, &robotGui);
    Server.StartServer();

    // Open the window
    mainWindow->setCentralWidget(win);
    win->show();
    mainWindow->show();
    return QApplication::exec();
}

