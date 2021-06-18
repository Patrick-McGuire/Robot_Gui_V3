#ifndef ROBOT_GUI_V3_BASEWIDGET_H
#define ROBOT_GUI_V3_BASEWIDGET_H
#include <string>
#include "QWidget"
#include "../WidgetInfo.h"
#include "../WidgetData.h"

class BaseWidget: public QWidget {

protected:
    std::string *_name;
    WidgetInfo *_configInfo;
    WidgetData *_widgetData;
    int _x;
    int _y;
public:
    /**
     * Constructor
     * @param name  name of widget
     * @param x     x position of the widget
     * @param y     y position of the widget
     */
    BaseWidget(QWidget *parent, WidgetInfo *configInfo, WidgetData *widgetData);

    /**
     * Sets the position of the widget on the screen
     * @param x     x position of the widget
     * @param y     y position of the widget
     */
    void setPosition(int x, int y);
};


#endif //ROBOT_GUI_V3_BASEWIDGET_H
