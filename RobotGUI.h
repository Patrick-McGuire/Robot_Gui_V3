#ifndef ROBOT_GUI_V3_ROBOTGUI_H
#define ROBOT_GUI_V3_ROBOTGUI_H
#include <QObject>
#include <QTimer>
#include "WidgetData.h"
#include "GUIMaker.h"
#include <QMainWindow>
#include "CustomWidgets/TabWidget.h"
#include "Configuration/ConfigStructs.h"

class RobotGUI : public QObject {
Q_OBJECT
public:
//    QTimer *timer;
//    GUIMaker *guiMaker;
    TabWidget *tabWidget;
    RobotGUI(QWidget *parent, WidgetData *widgetData, WidgetConfig *config, QMainWindow *mainWindow, int width, int height);

public slots:
    void updateGUI();
    void mousePress();
    void mouseRelease();
    void mouseMove();

private:
    WidgetData *_widgetData;
    WidgetConfig *_config;

    int _width;
    int _height;
    QMainWindow *_mainWindow;
};


#endif //ROBOT_GUI_V3_ROBOTGUI_H
