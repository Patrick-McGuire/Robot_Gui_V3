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
#include "CustomWidgets/SourceMapConfigWidgets/AttitudeWidget.h"
#include "WidgetData.h"
#include "Theme.h"

/**
 * Gets called in tabWidget to create a new subwidgets
 */
RobotGui::BaseWidget *RobotGui::GUIMaker::createWidget(QWidget *parent, const RobotGui::WidgetBaseConfig::SharedPtr &configInfo, RobotGui::WidgetData *widgetData, Theme *theme) {
    if (configInfo->type == RobotGui::WidgetConstants::TEXT_BOX) {
        return new TextBoxWidget(parent, configInfo, widgetData, theme);
    } else if (configInfo->type == RobotGui::WidgetConstants::VIDEO) {
        return new VideoWidget(parent, configInfo, widgetData, theme);
    } else if (configInfo->type == RobotGui::WidgetConstants::TAB) {
        return new TabWidget(parent, configInfo, widgetData, theme);
    } else if (configInfo->type == RobotGui::WidgetConstants::SIMPLE_BUTTON) {
        return new SimpleButtonWidget(parent, configInfo, widgetData, theme);
    } else if (configInfo->type == RobotGui::WidgetConstants::MULTI_BAR_GRAPH) {
        return new MultiBarGraphWidget(parent, configInfo, widgetData, theme);
    } else if (configInfo->type == RobotGui::WidgetConstants::ANNUNCIATOR_PANEL) {
        return new AnnunciatorWidget(parent, configInfo, widgetData, theme);
    } else if (configInfo->type == RobotGui::WidgetConstants::SIMPLE_CONSOLE) {
        return new SimpleConsoleWidget(parent, configInfo, widgetData, theme);
    } else if (configInfo->type == RobotGui::WidgetConstants::ROV_STATUS) {
        return new ROVStatusWidget(parent, configInfo, widgetData, theme);
    } else if (configInfo->type == RobotGui::WidgetConstants::COMPLETE_CONSOLE) {
        return new CompleteConsoleWidget(parent, configInfo, widgetData, theme);
    } else if (configInfo->type == RobotGui::WidgetConstants::MISSION_STATUS) {
        return new MissionStatusWidget(parent, configInfo, widgetData, theme);
    } else if (configInfo->type == RobotGui::WidgetConstants::DROP_DOWN_TEXT_BOX) {
        return new DropDownTextBoxWidget(parent, configInfo, widgetData, theme);
    } else if (configInfo->type == RobotGui::WidgetConstants::COMPASS) {
        return new CompassWidget(parent, configInfo, widgetData, theme);
    } else if (configInfo->type == RobotGui::WidgetConstants::LIVE_PLOT) {
        return new LivePlotWidget(parent, configInfo, widgetData, theme);
    } else if (configInfo->type == RobotGui::WidgetConstants::ATTITUDE_DISPLAY) {
        return new AttitudeWidget(parent, configInfo, widgetData, theme);
    } else {
        std::cout << "Can't create widget of type " << configInfo->type << std::endl;
    }
    return nullptr;
}
