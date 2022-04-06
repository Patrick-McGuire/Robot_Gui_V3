//
// Created by nathan on 1/26/22.
//

#ifndef ROBOT_GUI_V3_INTERFACESETTINGS_H
#define ROBOT_GUI_V3_INTERFACESETTINGS_H

#include "BaseSettingsPanel.h"
#include "../../WidgetData.h"
#include "../../Theme.h"

class InterfaceSettings : public BaseSettingsPanel {
public:
    InterfaceSettings(QWidget *parent, RobotGui::WidgetData *widgetData, RobotGui::Theme *theme);
};


#endif //ROBOT_GUI_V3_INTERFACESETTINGS_H
