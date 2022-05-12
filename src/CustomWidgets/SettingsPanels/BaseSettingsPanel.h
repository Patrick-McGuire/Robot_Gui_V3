//
// Created by nathan on 1/26/22.
//

#ifndef ROBOT_GUI_V3_BASESETTINGSPANEL_H
#define ROBOT_GUI_V3_BASESETTINGSPANEL_H

#include "../BaseStructure/BaseWidget.h"
#include "../../WidgetData.h"
#include "../../Theme.h"

namespace RobotGui {
    class BaseSettingsPanel : public RobotGui::BaseWidget {
    public:
        BaseSettingsPanel(QWidget *parent, WidgetData *widgetData, Theme *theme);


    };
}


#endif //ROBOT_GUI_V3_BASESETTINGSPANEL_H
