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
#include <QTabWidget>
#include <QMenu>

class BaseWidget: public QWidget {
Q_OBJECT
protected:
    QWidget *_parent;
    WidgetConfig_ptr _configInfo;
    WidgetData *_widgetData;
    const bool staticPos;

    /**
     * Updates data when widget is in focus, virtual
     */
    virtual void updateInFocus();

    /**
     * Updates data when widget is out of focus, virtual
     */
    virtual void updateNoFocus();

    /**
     * Updates data when widget comes into focus, virtual
     */
    virtual void updateOnInFocus();

    /**
     * Put any code that is common between update functions here and call in the other functions
     */
    virtual void customUpdate();

    /**
     * Used by widget collections to call setDraggability() in their children
     * @param _draggable if the widgets is draggable
     */
    virtual void customUpdateDraggability(bool _draggable);

    /**
     * Keeps track of the start of a click for widget dragging
     * @param event click QMouseEvent
     */
    void mousePressEvent(QMouseEvent *event) override;

    /**
     * Keeps track of the end of a click for widget dragging
     * @param event click QMouseEvent
     */
    void mouseReleaseEvent(QMouseEvent *event) override;

    /**
     * Moves the widget based provided event
     * @param event drag QMouseEvent
     */
    void mouseMoveEvent(QMouseEvent *event) override;

public:

    /**
     * Constructor
     * @param parent parent QWidget
     * @param configInfo config struct to create widget based off of
     * @param widgetData data passing structure to read data from at runtime
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


public slots:
    /**
     * Toggles the draggable state of this widget if widget is not static
     */
    void toggleDraggability();

private slots:
    /**
     * Shows a right click menu with various options
     * @param pos Point to open menu at
     */
    void showContextMenu(const QPoint &pos);

private:
    bool inFocusLast = true;
    bool clicked = false;
    int startX = 0;
    int startY = 0;
    int startWX = 0;
    int startWY = 0;
};

#endif //ROBOT_GUI_V3_BASEWIDGET_H
