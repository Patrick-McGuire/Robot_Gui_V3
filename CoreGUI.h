//
// Created by patrick on 11/15/21.
//

#ifndef ROBOT_GUI_V3_COREGUI_H
#define ROBOT_GUI_V3_COREGUI_H

#include <QWidget>
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

class RobotGUI;
class MenuWidget;

class CoreGUI : public QObject{
Q_OBJECT
public:
    CoreGUI(int argc, char** argv);
    int runGUI();

public slots:
    void reload();
    void reparseReload();
    void openReload();

private:
    void restartGUI();
    bool safeParse();
    std::string getFilePath();

    int argc;
    char **argv;
    WindowConfig_ptr windowConfig;
    AppConfig *appConfig;
    QApplication app;
    QMainWindow mainWindow;
    QWidget window;
    QWidget *wrapper;
    RobotGUI *currentRobotGUI;
};


#endif //ROBOT_GUI_V3_COREGUI_H
