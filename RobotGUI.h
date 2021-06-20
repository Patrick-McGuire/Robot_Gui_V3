#ifndef ROBOT_GUI_V3_ROBOTGUI_H
#define ROBOT_GUI_V3_ROBOTGUI_H
#include <QObject>
#include <QTimer>
#include "WidgetData.h"
#include "Configuration/TabInfo.h"
#include "GUIMaker.h"

class RobotGUI : public QObject {
Q_OBJECT
public:
    QTimer *timer;
    GUIMaker *guiMaker;
    RobotGUI(QWidget *parent, WidgetData *widgetData, std::vector<TabInfo*> *config);

public slots:
    void updateGUI();

private:
    WidgetData *_widgetData;
    std::vector<TabInfo*> *_config;
    std::vector<BaseWidget*> *allWidgets;
};


#endif //ROBOT_GUI_V3_ROBOTGUI_H
