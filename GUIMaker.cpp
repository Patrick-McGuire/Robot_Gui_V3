#include "GUIMaker.h"
#include <iostream>
#include <QTabWidget>

#include "CustomWidgets/MultiBarGraphWidget.h"

BaseWidget *GUIMaker::createWidget(QWidget *parent, const WidgetConfig_ptr &configInfo, WidgetData *widgetData) {
    if (configInfo->type == textBoxWidgetSTRID) {
        return new TextBoxWidget(parent, configInfo, widgetData);
    } else if (configInfo->type == videoWidgetSTRID) {
        return new VideoWidget(parent, configInfo, widgetData);
    } else if (configInfo->type == tabWidgetSTRID) {
        return new TabWidget(parent, configInfo, widgetData);
    } else if (configInfo->type == SIMPLE_BUTTON_WIDGET_STRID) {
        return new SimpleButtonWidget(parent, configInfo, widgetData);
    } else if (configInfo->type == MULTI_BAR_GRAPH_STRID) {
        return new MultiBarGraphWidget(parent, configInfo, widgetData);
    }
    return nullptr;
}
