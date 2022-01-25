//
// Created by nathan on 1/25/22.
//

#ifndef ROBOT_GUI_V3_SETTINGSTAB_H
#define ROBOT_GUI_V3_SETTINGSTAB_H

#include "BaseWidget.h"

#include "../WidgetData.h"

class SettingsTab : public BaseWidget {
public:
    SettingsTab(QWidget *parent, const RobotGui::WidgetConfig_ptr &configInfo, WidgetData *widgetData, Theme *_theme);
};


#endif //ROBOT_GUI_V3_SETTINGSTAB_H
