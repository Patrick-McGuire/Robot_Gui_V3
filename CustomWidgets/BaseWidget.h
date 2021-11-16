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
    bool inFocusLast = true;
    bool clicked = false;
    bool draggable;
    const bool staticPos;

    virtual void updateInFocus();
    virtual void updateNoFocus();
    virtual void updateOnInFocus();
    virtual void customUpdate();
    virtual void customUpdateDraggability(bool _draggable);

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

public:

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

    /**
     * Updates the widget from data passed though widgetData
     * @param activeParent QWidget, should be the parent of this instance if that parent is currently visible
     */
    void updateData(QWidget *activeParent);

    /**
     * Updates the widget from data passed though widgetData
     * @param focus weather or not the widget is in focus
     */
    void updateData(bool focus);

    /**
     * Sets the _draggable state of this widget if widget is not static
     * @param _draggable
     */
    void setDraggability(bool _draggable);

    /**
     * Toggles the draggable state of this widget if widget is not static
     */
    void toggleDraggability();


private:
    int startX = 0;
    int startY = 0;
    int startWX = 0;
    int startWY = 0;
};


#endif //ROBOT_GUI_V3_BASEWIDGET_H
