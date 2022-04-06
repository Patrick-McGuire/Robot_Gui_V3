//
// Created by nathan on 12/28/21.
//

#ifndef ROBOT_GUI_V3_MISSIONSTATUSWIDGET_H
#define ROBOT_GUI_V3_MISSIONSTATUSWIDGET_H

#include "BaseWidget.h"
#include "../WidgetData.h"
#include "../Theme.h"
#include <QLabel>

class MissionStatusWidget : public BaseWidget {
public:
    MissionStatusWidget(QWidget *parent, const RobotGui::WidgetConfig_ptr &configInfo, RobotGui::WidgetData *widgetData, RobotGui::Theme *theme);

    void updateInFocus() override;

    void customUpdateStyle() override ;

protected:
    std::string statusSource;
    std::string missionNameSource;
    std::string objectiveSource;
    int size;

    QLabel *statusBox;
    QLabel *missionNameBox;
    QLabel *objectiveBox;
};


#endif //ROBOT_GUI_V3_MISSIONSTATUSWIDGET_H
