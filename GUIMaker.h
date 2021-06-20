#ifndef ROBOT_GUI_V3_GUIMAKER_H
#define ROBOT_GUI_V3_GUIMAKER_H
#include <vector>
#include "Configuration/TabInfo.h"
#include "Configuration/WidgetInfo.h"
#include "CustomWidgets/BaseWidget.h"
#include "CustomWidgets/TextBoxWidget.h"
#include <QWidget>
#include <QTabWidget>

class GUIMaker {
private:
    std::vector<TabInfo*> *_config;
    WidgetData *_widgetData;
    QWidget *_parent;

    void createTab(std::vector<TabInfo*> *config);
public:
    QTabWidget *tabWidget;
    std::vector<BaseWidget*> *allWidgets;
    explicit GUIMaker(QWidget *parent, std::vector<TabInfo*> *config, WidgetData *widgetData);
};


#endif //ROBOT_GUI_V3_GUIMAKER_H
