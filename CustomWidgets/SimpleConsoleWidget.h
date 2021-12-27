//
// Created by nathan on 12/26/21.
//

#ifndef ROBOT_GUI_V3_SIMPLECONSOLEWIDGET_H
#define ROBOT_GUI_V3_SIMPLECONSOLEWIDGET_H

#include "BaseWidget.h"
#include "../WidgetData.h"

class SimpleConsoleWidget : public BaseWidget {
public:
    SimpleConsoleWidget(QWidget *parent, const RobotGui::WidgetConfig_ptr &configInfo, WidgetData *widgetData, Theme *theme);

    void updateInFocus() override;

    void paintEvent(QPaintEvent *_event) override;

    void adjustSize();

protected:
    std::string source;
    std::string title;
    bool drawTitle = false;
    int maxLineWidth = 0;
    int numberOfLines = 0;
};


#endif //ROBOT_GUI_V3_SIMPLECONSOLEWIDGET_H
