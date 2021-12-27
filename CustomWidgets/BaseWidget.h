#ifndef ROBOT_GUI_V3_BASEWIDGET_H
#define ROBOT_GUI_V3_BASEWIDGET_H

#include <string>
#include "QWidget"
#include "../WidgetData.h"
#include "QMouseEvent"
#include "../XML/rapidxml/rapidxml.hpp"
#include "../XML/rapidxml/rapidxml_print.hpp"
#include "../XML/rapidxml/rapidxml_utils.hpp"
#include <QTabWidget>
#include <QMenu>
#include "../Theme.h"


/**
 * @class BaseWidget
 * Custom QWidget that creates tabs with children widgets
 *
 * @author Patrick McGuire (Patrick-McGuire)
 */
class BaseWidget : public QWidget {
Q_OBJECT
public:
    /**
     * Constructor
     * @param _parent_ _parent_ QWidget
     * @param _configInfo config struct to create widget based off of
     * @param _widgetData data passing structure to read data from at runtime
     */
    BaseWidget(QWidget *_parent_, const RobotGui::WidgetConfig_ptr &_configInfo, WidgetData *_widgetData, Theme *_theme);

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
     * Updates the style of this widget, to be overwritten by derived
     * @param overwrite weather to overwrite any attributes with theme
     */
    virtual void customUpdateStyle(const std::string &backgroundColor, const std::string &widgetBackgroundColor, const std::string &bodyTextColor, const std::string &titleTextColor,
                                   const std::string &borderColor);

    /**
     * Updates the style of children widget, to be overwritten by derived
     * @param overwrite weather to overwrite any attributes with theme
     */
    virtual void updateChildrenStyle();

    /**
     * Updates the style of this widget
     * @param _theme them for this widget to use
     * @param overwrite weather to overwrite any attributes with theme
     */
    void updateStyle();

    /**
     * Sets the _draggable state of this widget if widget is not static
     * @param _draggable
     */
    void setDraggability(bool _draggable);

protected:
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

    void paintEvent(QPaintEvent *_event) override;

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

    QWidget *_parent;
    RobotGui::WidgetConfig_ptr configInfo;
    WidgetData *widgetData;
    const bool staticPos;
    bool drawBorder = true;
    Theme *theme;

    // These register weather or not the current widget can update these attributes
    // Set these in the constructor of any derived class
    bool styledBackground = false;
    bool styledText = false;
    bool styledHeader = false;
    bool styledSeeThroughBackground = false;
    bool styledBorderColor = false;
    bool styledWidgetBackgroundColor = false;

public slots:

    /**
     * Toggles the draggable state of this widget if widget is not static
     */
    void toggleDraggability();

    /**
     * Sets the background color for this widget
     * @param channelAction Stores the color to set
     */
    void setBackgroundColor(QAction *channelAction);

    /**
     * Sets the text color for this widget
     * @param channelAction Stores the color to set
     */
    void setTextColor(QAction *channelAction);

private slots:

    /**
     * Shows a right click menu with various options
     * @param pos Point to open menu at
     */
    void showContextMenu(const QPoint &pos);

private:
    const char *const CONTEXT_MENU_NAME = "TempContextMenuName";
    bool inFocusLast = true;
    bool clicked = false;
    int startX = 0;
    int startY = 0;
    int startWX = 0;
    int startWY = 0;
};

#endif //ROBOT_GUI_V3_BASEWIDGET_H
