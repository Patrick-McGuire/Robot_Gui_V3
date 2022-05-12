#include "GUIMaker.h"
#include <iostream>
#include <QTabWidget>

#include "CustomWidgets/LineConfigWidgets/MultiBarGraphWidget.h"
#include "CustomWidgets/AnnunciatorWidget.h"
#include "CustomWidgets/SimpleConsoleWidget.h"
#include "CustomWidgets/SourceMapConfigWidgets/ROVStatusWidget.h"
#include "CustomWidgets/CompleteConsoleWidget.h"
#include "CustomWidgets/SourceMapConfigWidgets/MissionStatusWidget.h"
#include "CustomWidgets/DropDownTextBoxWidget.h"
#include "CustomWidgets/LineConfigWidgets/LivePlotWidget.h"
#include "CustomWidgets/CompassWidget.h"
#include "WidgetData.h"
#include "Theme.h"

/**
 * Gets called in tabWidget to create a new subwidgets
 */
RobotGui::BaseWidget *RobotGui::GUIMaker::createWidget(QWidget *parent, const RobotGui::WidgetBaseConfig::SharedPtr &configInfo, RobotGui::WidgetData *widgetData, Theme *theme) {
    if (configInfo->type == RobotGui::TEXT_BOX) {
        return new TextBoxWidget(parent, configInfo, widgetData, theme);
    } else if (configInfo->type == RobotGui::VIDEO) {
        return new VideoWidget(parent, configInfo, widgetData, theme);
    } else if (configInfo->type == RobotGui::TAB) {
        return new TabWidget(parent, configInfo, widgetData, theme);
    } else if (configInfo->type == RobotGui::SIMPLE_BUTTON) {
        return new SimpleButtonWidget(parent, configInfo, widgetData, theme);
    } else if (configInfo->type == RobotGui::MULTI_BAR_GRAPH) {
        return new MultiBarGraphWidget(parent, configInfo, widgetData, theme);
    } else if (configInfo->type == RobotGui::ANNUNCIATOR_PANEL) {
        return new AnnunciatorWidget(parent, configInfo, widgetData, theme);
    } else if (configInfo->type == RobotGui::SIMPLE_CONSOLE) {
        return new SimpleConsoleWidget(parent, configInfo, widgetData, theme);
    } else if (configInfo->type == RobotGui::ROV_STATUS) {
        return new ROVStatusWidget(parent, configInfo, widgetData, theme);
    } else if (configInfo->type == RobotGui::COMPLETE_CONSOLE) {
        return new CompleteConsoleWidget(parent, configInfo, widgetData, theme);
    } else if (configInfo->type == RobotGui::MISSION_STATUS) {
        return new MissionStatusWidget(parent, configInfo, widgetData, theme);
    } else if (configInfo->type == RobotGui::DROP_DOWN_TEXT_BOX) {
        return new DropDownTextBoxWidget(parent, configInfo, widgetData, theme);
    } else if (configInfo->type == RobotGui::COMPASS) {
        return new CompassWidget(parent, configInfo, widgetData, theme);
    } else if (configInfo->type == RobotGui::LIVE_PLOT) {
        return new LivePlotWidget(parent, configInfo, widgetData, theme);
    } else {
        std::cout << "Can't create widget of type " << configInfo->type << std::endl;
    }
    return nullptr;
}
