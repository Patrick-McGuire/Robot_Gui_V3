#include "LineConfig.h"

//////// Mandatory constructors ////////
RobotGui::LineConfig::LineConfig(RobotGui::WidgetType _type) : WidgetBaseConfig(_type) {}

RobotGui::LineConfig::SharedPtr RobotGui::LineConfig::create(RobotGui::WidgetType _type) {
    return RobotGui::LineConfig::SharedPtr(new LineConfig(_type));
}

RobotGui::LineConfig::SharedPtr RobotGui::LineConfig::create(const std::string &_type) {
    return RobotGui::LineConfig::SharedPtr(new LineConfig(getType(_type)));
}

RobotGui::LineConfig::SharedPtr RobotGui::LineConfig::create() {
    return RobotGui::LineConfig::SharedPtr(new LineConfig(NO_TYPE));
}
//////// Mandatory constructors ////////