#ifndef ROBOT_GUI_V3_BASEWIDGET_H
#define ROBOT_GUI_V3_BASEWIDGET_H
#include <string>
#include "QWidget"
#include "../Configuration/WidgetInfo.h"
#include "../WidgetData.h"
#include "QMouseEvent"

class BaseWidget: public QWidget {
Q_OBJECT
protected:
    std::string *_name;
    WidgetInfo *_configInfo;
    WidgetData *_widgetData;
    int _x{};
    int _y{};

    int startX{};
    int startY{};
    int startWX;
    int startWY;
    bool clicked{};
    QWidget *_parent;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
public:
    bool draggable;

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

    virtual void updateData();
};


#endif //ROBOT_GUI_V3_BASEWIDGET_H
