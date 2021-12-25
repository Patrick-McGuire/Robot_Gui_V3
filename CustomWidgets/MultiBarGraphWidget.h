//
// Created by nathan on 12/25/21.
//

#ifndef ROBOT_GUI_V3_MULTIBARGRAPHWIDGET_H
#define ROBOT_GUI_V3_MULTIBARGRAPHWIDGET_H

#include "BaseWidget.h"
#include "WidgetParts/SimpleBarGraph.h"

class MultiBarGraphWidget : public BaseWidget {
public:
    MultiBarGraphWidget(QWidget *parent, const WidgetConfig_ptr &configInfo, WidgetData *widgetData);

    void updateInFocus();

    static void parseXml(const WidgetConfig_ptr &parentConfig, rapidxml::xml_node<> *node);

protected:
    int size = 200;

    std::vector<BaseGraphDisplay *> subGraphVector;
    std::vector<std::string> subGraphSourcesVector;
};


#endif //ROBOT_GUI_V3_MULTIBARGRAPHWIDGET_H
