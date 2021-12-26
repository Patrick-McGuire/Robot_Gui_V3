#include "GUIMaker.h"
#include <iostream>
#include <QTabWidget>

#include "CustomWidgets/MultiBarGraphWidget.h"
#include "CustomWidgets/AnnunciatorWidget.h"

/*
 * Gets called in tabWidget to create a new subwidgets
 */
BaseWidget *GUIMaker::createWidget(QWidget *parent, const WidgetConfig_ptr &configInfo, WidgetData *widgetData) {
    if (configInfo->type == TEXT_BOX_WIDGET_STRID) {
        return new TextBoxWidget(parent, configInfo, widgetData);
    } else if (configInfo->type == VIDEO_WIDGET_STRID) {
        return new VideoWidget(parent, configInfo, widgetData);
    } else if (configInfo->type == TAB_WIDGET_STRID) {
        return new TabWidget(parent, configInfo, widgetData);
    } else if (configInfo->type == SIMPLE_BUTTON_WIDGET_STRID) {
        return new SimpleButtonWidget(parent, configInfo, widgetData);
    } else if (configInfo->type == MULTI_BAR_GRAPH_STRID) {
        return new MultiBarGraphWidget(parent, configInfo, widgetData);
    } else if (configInfo->type == ANNUNCIATOR_PANEL_STRID) {
        return new AnnunciatorWidget(parent, configInfo, widgetData);
    } else {
        std::cout << "Can't create widget of type " << configInfo->type << std::endl;
    }
    return nullptr;
}
