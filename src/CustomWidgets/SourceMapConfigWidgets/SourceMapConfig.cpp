#include "SourceMapConfig.h"

//////// Mandatory constructors ////////
RobotGui::SourceMapConfig::SourceMapConfig(RobotGui::WidgetType _type) : WidgetBaseConfig(_type) {}

RobotGui::SourceMapConfig::SharedPtr RobotGui::SourceMapConfig::create(RobotGui::WidgetType _type) {
    return RobotGui::SourceMapConfig::SharedPtr(new SourceMapConfig(_type));
}

RobotGui::SourceMapConfig::SharedPtr RobotGui::SourceMapConfig::create(const std::string &_type) {
    return RobotGui::SourceMapConfig::SharedPtr(new SourceMapConfig(getType(_type)));
}

RobotGui::SourceMapConfig::SharedPtr RobotGui::SourceMapConfig::create() {
    return RobotGui::SourceMapConfig::SharedPtr(new SourceMapConfig(NO_TYPE));
}
//////// Mandatory constructors ////////