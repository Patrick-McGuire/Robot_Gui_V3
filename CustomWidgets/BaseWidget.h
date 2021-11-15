#ifndef ROBOT_GUI_V3_BASEWIDGET_H
#define ROBOT_GUI_V3_BASEWIDGET_H
#include <string>
#include "QWidget"
#include "../ConfigStructs.h"
#include "../WidgetData.h"
#include "QMouseEvent"
#include "../XML/rapidxml/rapidxml.hpp"
#include "../XML/rapidxml/rapidxml_print.hpp"
#include "../XML/rapidxml/rapidxml_utils.hpp"

class BaseWidget: public QWidget {
Q_OBJECT
protected:
    QWidget *_parent;
    WidgetConfig_ptr _configInfo;
    WidgetData *_widgetData;
    bool inFocusLast;
    int x = 0;
    int y = 0;
    int startX = 0;
    int startY = 0;
    int startWX = 0;
    int startWY = 0;
    bool clicked = false;

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
    BaseWidget(QWidget *parent, const WidgetConfig_ptr& configInfo, WidgetData *widgetData);

    /**
     * Sets the position of the widget on the screen
     * @param x     x position of the widget
     * @param y     y position of the widget
     */
    void setPosition(int x, int y);

    void updateData(QWidget *activeParent);
    void updateData(bool focus);


private:
    virtual void updateInFocus();
    virtual void updateNoFocus();
    virtual void updateOnInFocus();
    virtual void customUpdate();
};


#endif //ROBOT_GUI_V3_BASEWIDGET_H
