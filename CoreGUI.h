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

class CoreGUI : public QObject{
Q_OBJECT
public:
    CoreGUI(int argc, char** argv);
    int runGUI();

public slots:
    void restartGUI();

private:
    int argc;
    char **argv;
    AppConfig appConfig;
    QApplication app;
    QMainWindow mainWindow;
    QWidget window;
    QWidget *wrapper;
    RobotGUI *currentRobotGUI;
};


#endif //ROBOT_GUI_V3_COREGUI_H
