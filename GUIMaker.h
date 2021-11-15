#ifndef ROBOT_GUI_V3_GUIMAKER_H
#define ROBOT_GUI_V3_GUIMAKER_H
#include <vector>
#include "CustomWidgets/BaseWidget.h"
#include "CustomWidgets/TextBoxWidget.h"
#include "CustomWidgets/TabWidget.h"
#include "CustomWidgets/VideoWidget.h"
#include <QWidget>
#include <QTabWidget>

class GUIMaker {
public:
    static BaseWidget* createWidget(QWidget *parent, WidgetConfig_ptr configInfo, WidgetData *widgetData);
};

#endif //ROBOT_GUI_V3_GUIMAKER_H
