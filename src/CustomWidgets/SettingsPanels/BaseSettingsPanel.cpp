//
// Created by nathan on 1/26/22.
//

#include "BaseSettingsPanel.h"
#include "../../WidgetData.h"
#include "../../Theme.h"


std::shared_ptr<RobotGui::WidgetConfig> CreateBlankWidgetConfigPointer() {
    auto newConfigInfo = std::make_shared<RobotGui::WidgetConfig>();
    newConfigInfo->backgroundColor = RobotGui::Xml::THEME_CONST;
    newConfigInfo->foregroundColor = RobotGui::Xml::THEME_CONST;
    newConfigInfo->textColor = RobotGui::Xml::THEME_CONST;
    newConfigInfo->headerColor = RobotGui::Xml::THEME_CONST;
    newConfigInfo->borderColor = RobotGui::Xml::THEME_CONST;
    return newConfigInfo;
}

RobotGui::BaseSettingsPanel::BaseSettingsPanel(QWidget *parent, RobotGui::WidgetData *widgetData, RobotGui::Theme *theme) : BaseWidget(parent, CreateBlankWidgetConfigPointer(), widgetData, theme) {

}
