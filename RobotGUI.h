#ifndef ROBOT_GUI_V3_ROBOTGUI_H
#define ROBOT_GUI_V3_ROBOTGUI_H
#include <QObject>
#include <QTimer>
#include "WidgetData.h"
#include "GUIMaker.h"
#include <QMainWindow>
#include "CustomWidgets/TabWidget.h"
#include "ConfigStructs.h"
#include "QMenuBar"
#include "Menu.h"

class RobotGUI : public QObject {
Q_OBJECT
public:
    TabWidget *tabWidget;
    RobotGUI(QWidget *parent, QMainWindow *mainWindow, WidgetData *widgetData, AppConfig *config, const std::string& configPath);

public slots:
    void updateGUI();

private:
    WidgetData *_widgetData;
//    WidgetConfig *_config;
    QMainWindow *_mainWindow;
    QBoxLayout *layout;
    Menu *menu;
};


#endif //ROBOT_GUI_V3_ROBOTGUI_H
