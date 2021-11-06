#ifndef ROBOT_GUI_V3_BASEWIDGET_H
#define ROBOT_GUI_V3_BASEWIDGET_H
#include <string>
#include "QWidget"
#include "../Configuration/WidgetInfo.h"
#include "../WidgetData.h"
#include "QMouseEvent"
#include "../XML/rapidxml/rapidxml.hpp"
#include "../XML/rapidxml/rapidxml_print.hpp"
#include "../XML/rapidxml/rapidxml_utils.hpp"

class BaseWidget: public QWidget {
Q_OBJECT
protected:
    std::string *_name;
    WidgetInfo *_configInfo;
    WidgetData *_widgetData;
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
    BaseWidget(QWidget *parent, WidgetInfo *configInfo, WidgetData *widgetData);

    /**
     * Sets the position of the widget on the screen
     * @param x     x position of the widget
     * @param y     y position of the widget
     */
    void setPosition(int x, int y);

    virtual void updateData();

    /**
     * Adds widget type specific config to the specified struct
     * @param[out] parentConfig struct to configure
     * @param[in] node xml node to get data from
     */
    static void parseXml(struct WidgetConfig *parentConfig, rapidxml::xml_node<> *node);

private:
    virtual void updateInFocus();
    virtual void updateNoFocus();
    virtual void updateOnInFocus();
};


#endif //ROBOT_GUI_V3_BASEWIDGET_H
