#include "GUIMaker.h"
#include <iostream>
#include <QTabWidget>

#include "CustomWidgets/MultiBarGraphWidget.h"

BaseWidget *GUIMaker::createWidget(QWidget *parent, const RobotGui::WidgetConfig_ptr &configInfo, WidgetData *widgetData) {
    if (configInfo->type == RobotGui::TEXT_BOX_WIDGET_STRID) {
        return new TextBoxWidget(parent, configInfo, widgetData);
    } else if (configInfo->type == RobotGui::VIDEO_WIDGET_STRID) {
        return new VideoWidget(parent, configInfo, widgetData);
    } else if (configInfo->type == RobotGui::TAB_WIDGET_STRID) {
        return new TabWidget(parent, configInfo, widgetData);
    } else if (configInfo->type == RobotGui::SIMPLE_BUTTON_WIDGET_STRID) {
        return new SimpleButtonWidget(parent, configInfo, widgetData);
    } else if (configInfo->type == RobotGui::MULTI_BAR_GRAPH_STRID) {
        return new MultiBarGraphWidget(parent, configInfo, widgetData);
    }
    return nullptr;
}
