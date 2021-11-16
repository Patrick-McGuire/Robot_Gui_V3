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
#include "CoreGUI.h"

class LocalServer;
class MenuWidget;
class CoreGUI;

class RobotGUI : public QWidget {
Q_OBJECT
public:
    RobotGUI(QWidget *_parent, QMainWindow *_mainWindow, AppConfig *_appConfig, CoreGUI *_coreGui, const WindowConfig_ptr& _config);
    ~RobotGUI();

public slots:
    void updateGUI();

signals:
    void restartThing();

private:
    WindowConfig_ptr config;
    CoreGUI *coreGui;
    WidgetData *widgetData;
    QMainWindow *mainWindow;
    MenuWidget *menu;
    BaseWidget *coreWidget;
    LocalServer *server;
    AppConfig *appConfig;
    QWidget *parent;
};


#endif //ROBOT_GUI_V3_ROBOTGUI_H
