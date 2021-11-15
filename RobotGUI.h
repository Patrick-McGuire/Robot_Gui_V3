#ifndef ROBOT_GUI_V3_ROBOTGUI_H
#define ROBOT_GUI_V3_ROBOTGUI_H
#include <QObject>
#include <QTimer>
#include "WidgetData.h"
#include "GUIMaker.h"
#include <QMainWindow>
#include "CustomWidgets/TabWidget.h"
#include "ConfigStructs.h"
#include "CustomWidgets/MenuWidget.h"
#include "iostream"
#include <vector>
#include <QApplication>
#include "Networking/LocalServer.h"

class LocalServer;

class RobotGUI : public QWidget {
Q_OBJECT
public:
    RobotGUI(QWidget *_parent, QMainWindow *_mainWindow, AppConfig *_appConfig);

public slots:
    void updateGUI();

private:
    WidgetData *widgetData;
    QMainWindow *mainWindow;
    MenuWidget *menu;
    BaseWidget *coreWidget;
    LocalServer *server;
    AppConfig *appConfig;
    QWidget *parent;
};


#endif //ROBOT_GUI_V3_ROBOTGUI_H
