//
// Created by nathan on 12/27/21.
//

#ifndef ROBOT_GUI_V3_ROVSTATUSWIDGET_H
#define ROBOT_GUI_V3_ROVSTATUSWIDGET_H

#include "BaseWidget.h"
#include "../WidgetData.h"

#include <QLabel>

class ROVStatusWidget : public BaseWidget {
public:
    ROVStatusWidget(QWidget *parent, const RobotGui::WidgetConfig_ptr &configInfo, RobotGui::WidgetData *widgetData, Theme *theme);

    void updateInFocus() override;

    void customUpdateStyle() override;

protected:
    std::string statusSource;
    std::string armedSource;
    std::string allowedToArmSource;
    std::string modeSource;
    std::string runtimeSource;
    std::string timeSource;
    int size;

    QLabel *statusBox;
    QLabel *armingBox;
    QLabel *modeBox;
    QLabel *timeBox;
    QLabel *runtimeBox;
};


#endif //ROBOT_GUI_V3_ROVSTATUSWIDGET_H
