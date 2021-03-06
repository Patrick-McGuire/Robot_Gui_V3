//
// Created by nathan on 1/25/22.
//

#ifndef ROBOT_GUI_V3_SETTINGSTAB_H
#define ROBOT_GUI_V3_SETTINGSTAB_H

#include "BaseStructure/BaseWidget.h"

#include "../WidgetData.h"

#include "WidgetParts/SideTabWidget.h"
#include "SettingsPanels/BaseSettingsPanel.h"
#include "../WidgetData.h"
#include "../Theme.h"

namespace RobotGui {
    class SettingsTab : public BaseWidget {
    public:
        SettingsTab(QWidget *parent, const WidgetBaseConfig::SharedPtr &configInfo, WidgetData *widgetData, Theme *_theme);

        void addPanel(BaseSettingsPanel *new_panel, const std::string &name);

    protected:
        void updateInFocus() override;

        void customUpdateStyle() override;

    protected:
        SideTabWidget *sideTabWidget;

        std::vector<BaseSettingsPanel *> settingsPanels;
    };
}


#endif //ROBOT_GUI_V3_SETTINGSTAB_H
