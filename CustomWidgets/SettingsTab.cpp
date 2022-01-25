//
// Created by nathan on 1/25/22.
//

#include "SettingsTab.h"

#include "QGridLayout"
#include "QLabel"

SettingsTab::SettingsTab(QWidget *parent, const RobotGui::WidgetConfig_ptr &configInfo, WidgetData *widgetData, Theme *_theme) : BaseWidget(parent, configInfo, widgetData, _theme) {
    sideTabWidget = new SideTabWidget();
    sideTabWidget->show();

    auto layout = new QGridLayout();
    layout->addWidget(sideTabWidget);
    layout->setMargin(0);
    setLayout(layout);

    auto tab1 = new QLabel();
    auto tab2 = new QLabel();
    tab1->setText("HI");
    tab2->setText("AAA");

    sideTabWidget->addTab("Test1", tab1);
    sideTabWidget->addTab("Test2", tab2);
}
