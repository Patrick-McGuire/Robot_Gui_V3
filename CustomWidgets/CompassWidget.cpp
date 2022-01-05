//
// Created by nathan on 12/30/21.
//

#include "CompassWidget.h"

CompassWidget::CompassWidget(QWidget *parent, const RobotGui::WidgetConfig_ptr &configInfo, WidgetData *widgetData, Theme *theme) : BaseWidget(parent, configInfo, widgetData, theme) {
    compassDisplay = new CompassDisplay(widgetData, this);

    styledBackground = true;
    styledSeeThroughBackground = true;

    if (configInfo->size != 0) {
        compassDisplay->setSize(configInfo->size);
    }

    adjustSize();
}

void CompassWidget::updateInFocus() {
    double yaw = widgetData->getJson()->mapGet(configInfo->source)->getDouble();
    compassDisplay->setYaw(yaw);
}
