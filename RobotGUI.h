#ifndef ROBOT_GUI_V3_ROBOTGUI_H
#define ROBOT_GUI_V3_ROBOTGUI_H
#include <QObject>
#include <QTimer>
#include "WidgetData.h"
#include "Configuration/TabInfo.h"
#include "GUIMaker.h"
#include <QMainWindow>

class RobotGUI : public QObject {
Q_OBJECT
public:
//    QTimer *timer;
    GUIMaker *guiMaker;
    RobotGUI(QWidget *parent, WidgetData *widgetData, std::vector<TabInfo*> *config, QMainWindow *mainWindow, int width, int height);

public slots:
    void updateGUI();
    void mousePress();
    void mouseRelease();
    void mouseMove();

private:
    WidgetData *_widgetData;
    std::vector<TabInfo*> *_config;
    std::vector<BaseWidget*> *allWidgets;
    int _width;
    int _height;
    QMainWindow *_mainWindow;
};


#endif //ROBOT_GUI_V3_ROBOTGUI_H
