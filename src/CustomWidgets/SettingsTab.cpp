//
// Created by nathan on 1/25/22.
//

#include "SettingsTab.h"

#include "QGridLayout"
#include "QLabel"

#include "SettingsPanels/BaseSettingsPanel.h"
#include "SettingsPanels/InterfaceSettings.h"
#include "SettingsPanels/RawDataView.h"
#include "../WidgetData.h"

SettingsTab::SettingsTab(QWidget *parent, const RobotGui::WidgetConfig_ptr &configInfo, RobotGui::WidgetData *widgetData, Theme *_theme) : BaseWidget(parent, configInfo, widgetData, _theme) {
    sideTabWidget = new SideTabWidget();
    sideTabWidget->show();
    drawBorder = false;

    auto layout = new QGridLayout();
    layout->addWidget(sideTabWidget);
    layout->setContentsMargins(0, 0, 1, 2);
    setLayout(layout);

    addPanel(new InterfaceSettings(nullptr, widgetData, _theme), "Interface Settings");
    addPanel(new BaseSettingsPanel(nullptr, widgetData, _theme), "Test Panel");
    addPanel(new RawDataView(nullptr, widgetData, _theme), "Raw Data View");
}

void SettingsTab::addPanel(BaseSettingsPanel *new_panel, const std::string &name) {
    sideTabWidget->addTab(name, new_panel);
    settingsPanels.push_back(new_panel);
}

void SettingsTab::updateInFocus() {
    for (auto &panel: settingsPanels) {
        panel->updateData(true);
    }
}

void SettingsTab::customUpdateStyle() {
    for (auto &panel: settingsPanels) {
        panel->updateStyle();
    }

    sideTabWidget->setColorStrings(backgroundColor, bodyTextColor, borderColor);
}
