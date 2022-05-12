//
// Created by nathan on 5/2/22.
//

#include "AttitudeWidget.h"

#include "../../../lib/CommonFunctions.h"
#include "SourceMapConfig.h"
#include "../BaseStructure/WidgetBaseConfig.h"

RobotGui::AttitudeWidget::AttitudeWidget(QWidget *parent, const RobotGui::WidgetBaseConfig::SharedPtr &configInfo, RobotGui::WidgetData *widgetData, RobotGui::Theme *theme) : BaseWidget(parent, configInfo, widgetData, theme) {
    if(configInfo->type == ATTITUDE_DISPLAY) {
        sourceMapConfig = std::dynamic_pointer_cast<SourceMapConfig>(configInfo);
    } else {
        sourceMapConfig = SourceMapConfig::create();
    }

    rollSource = CommonFunctions::GetStringFromMap(sourceMapConfig->sourceMap, "rollSource", "roll");
    pitchSource = CommonFunctions::GetStringFromMap(sourceMapConfig->sourceMap, "pitchSource", "pitch");

    attitudeDisplay = new AttitudeDisplay(widgetData, this);

    adjustSize();
}

void RobotGui::AttitudeWidget::parseXml(const RobotGui::WidgetBaseConfig::SharedPtr &parentConfig, rapidxml::xml_node<> *node) {
    SourceMapConfig::SharedPtr config = std::dynamic_pointer_cast<SourceMapConfig>(parentConfig);
    for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        std::string attrName = attr->name();                                            // Get the name of the current attribute
        std::string attrVal = attr->value();                                            // Get the value of the current attribute
        if (attrName.find("Source") != std::string::npos) {
            config->sourceMap[attrName] = attrVal;
        }
    }
}

void RobotGui::AttitudeWidget::updateInFocus() {
    double roll = widgetData->getJson()->mapGet(rollSource)->getDouble();
    double pitch = widgetData->getJson()->mapGet(pitchSource)->getDouble();

    attitudeDisplay->setRollPitch(roll, pitch);
}
