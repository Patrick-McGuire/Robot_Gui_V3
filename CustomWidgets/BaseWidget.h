#ifndef ROBOT_GUI_V3_BASEWIDGET_H
#define ROBOT_GUI_V3_BASEWIDGET_H
#include <string>
#include "QWidget"
#include "../Configuration/WidgetInfo.h"
#include "../Configuration/ConfigStructs.h"
#include "../WidgetData.h"
#include "QMouseEvent"
#include "../XML/rapidxml/rapidxml.hpp"
#include "../XML/rapidxml/rapidxml_print.hpp"
#include "../XML/rapidxml/rapidxml_utils.hpp"

class BaseWidget: public QWidget {
Q_OBJECT
protected:
    std::string *_name;
//    WidgetConfig *_widgetConfig;
    WidgetConfig *_configInfo;
    WidgetData *_widgetData;
    bool inFocusLast;
    int _x;
    int _y;

    int startX;
    int startY;
    int startWX;
    int startWY;
    bool clicked;
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
    BaseWidget(QWidget *parent, WidgetConfig *configInfo, WidgetData *widgetData);

    /**
     * Sets the position of the widget on the screen
     * @param x     x position of the widget
     * @param y     y position of the widget
     */
    void setPosition(int x, int y);

    void updateData(QWidget *activeParent);


private:
    virtual void updateInFocus();
    virtual void updateNoFocus();
    virtual void updateOnInFocus();
    virtual void customUpdate();
};


#endif //ROBOT_GUI_V3_BASEWIDGET_H
