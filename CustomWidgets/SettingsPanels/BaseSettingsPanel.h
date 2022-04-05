//
// Created by nathan on 1/26/22.
//

#ifndef ROBOT_GUI_V3_BASESETTINGSPANEL_H
#define ROBOT_GUI_V3_BASESETTINGSPANEL_H

#include "../BaseWidget.h"
#include "../../WidgetData.h"

class BaseSettingsPanel : public BaseWidget {
public:
    BaseSettingsPanel(QWidget *parent, RobotGui::WidgetData *widgetData, Theme *theme);


};


#endif //ROBOT_GUI_V3_BASESETTINGSPANEL_H
