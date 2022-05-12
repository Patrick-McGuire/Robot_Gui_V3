//
// Created by nathan on 12/30/21.
//

#include "CompassWidget.h"
#include "../WidgetData.h"
#include "../Theme.h"
#include "BaseStructure/BaseWidget.h"

RobotGui::CompassWidget::CompassWidget(QWidget *parent, const RobotGui::WidgetBaseConfig::SharedPtr &configInfo, RobotGui::WidgetData *widgetData, RobotGui::Theme *theme) : BaseWidget(parent, configInfo, widgetData, theme) {
    compassDisplay = new CompassDisplay(widgetData, this);

    styledBackground = true;
    styledSeeThroughBackground = true;

    if (configInfo->size.is_initialized() && configInfo->size != 0) {
        compassDisplay->setSize(configInfo->size.get());
    }

    adjustSize();
}

void RobotGui::CompassWidget::updateInFocus() {
    if(configInfo->source.is_initialized()) {
        double yaw = widgetData->getJson()->mapGet(configInfo->source.get())->getDouble();
        compassDisplay->setYaw(yaw);
    }
}
