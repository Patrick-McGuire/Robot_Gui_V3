//
// Created by nathan on 5/2/22.
//

#include "AttitudeWidget.h"

#include "../../lib/CommonFunctions.h"

RobotGui::AttitudeWidget::AttitudeWidget(QWidget *parent, const RobotGui::WidgetConfig_ptr &configInfo, RobotGui::WidgetData *widgetData, RobotGui::Theme *theme) : BaseWidget(parent, configInfo, widgetData, theme) {
    rollSource = CommonFunctions::GetStringFromMap(configInfo->sourceMap, "rollSource", "roll");
    pitchSource = CommonFunctions::GetStringFromMap(configInfo->sourceMap, "pitchSource", "pitch");

    attitudeDisplay = new AttitudeDisplay(widgetData, this);

    adjustSize();
}

void RobotGui::AttitudeWidget::updateInFocus() {
    double roll = widgetData->getJson()->mapGet(rollSource)->getDouble();
    double pitch = widgetData->getJson()->mapGet(pitchSource)->getDouble();

    attitudeDisplay->setRollPitch(roll, pitch);
}
