#include "GUIMaker.h"
#include <iostream>
#include <QTabWidget>

#include "CustomWidgets/MultiBarGraphWidget.h"
#include "CustomWidgets/AnnunciatorWidget.h"
#include "CustomWidgets/SimpleConsoleWidget.h"
#include "CustomWidgets/ROVStatusWidget.h"
#include "CustomWidgets/CompleteConsoleWidget.h"
#include "CustomWidgets/MissionStatusWidget.h"

/*
 * Gets called in tabWidget to create a new subwidgets
 */
BaseWidget *GUIMaker::createWidget(QWidget *parent, const RobotGui::WidgetConfig_ptr &configInfo, WidgetData *widgetData, Theme *theme) {
    if (configInfo->type == RobotGui::TEXT_BOX_WIDGET_STRID) {
        return new TextBoxWidget(parent, configInfo, widgetData, theme);
    } else if (configInfo->type == RobotGui::VIDEO_WIDGET_STRID) {
        return new VideoWidget(parent, configInfo, widgetData, theme);
    } else if (configInfo->type == RobotGui::TAB_WIDGET_STRID) {
        return new TabWidget(parent, configInfo, widgetData, theme);
    } else if (configInfo->type == RobotGui::SIMPLE_BUTTON_WIDGET_STRID) {
        return new SimpleButtonWidget(parent, configInfo, widgetData, theme);
    } else if (configInfo->type == RobotGui::MULTI_BAR_GRAPH_STRID) {
        return new MultiBarGraphWidget(parent, configInfo, widgetData, theme);
    } else if (configInfo->type == RobotGui::ANNUNCIATOR_PANEL_STRID) {
        return new AnnunciatorWidget(parent, configInfo, widgetData, theme);
    } else if (configInfo->type == RobotGui::SIMPLE_CONSOLE_WIDGET_STRID) {
        return new SimpleConsoleWidget(parent, configInfo, widgetData, theme);
    } else if (configInfo->type == RobotGui::ROV_STATUS_WIDGET_STRID) {
        return new ROVStatusWidget(parent, configInfo, widgetData, theme);
    } else if (configInfo->type == RobotGui::COMPLETE_CONSOLE_WIDGET_STRID) {
        return new CompleteConsoleWidget(parent, configInfo, widgetData, theme);
    } else if (configInfo->type == RobotGui::MISSION_STATUS_WIDGET_STRID) {
        return new MissionStatusWidget(parent, configInfo, widgetData, theme);
    } else {
        std::cout << "Can't create widget of type " << configInfo->type << std::endl;
    }
    return nullptr;
}
