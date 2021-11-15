#include "GUIMaker.h"
#include <iostream>
#include <QTabWidget>

BaseWidget *GUIMaker::createWidget(QWidget *parent, const WidgetConfig_ptr& configInfo, WidgetData *widgetData) {
    if(configInfo->type == textBoxWidgetSTRID) {
        return new TextBoxWidget(parent, configInfo, widgetData);
    } else if(configInfo->type == videoWidgetSTRID) {
        return new VideoWidget(parent, configInfo, widgetData);
    } else if(configInfo->type == tabWidgetSTRID) {
        return new TabWidget(parent, configInfo, widgetData);
    }
    return nullptr;
}
