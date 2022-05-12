#include "WidgetCollectionConfig.h"

//////// Mandatory constructors ////////
RobotGui::WidgetCollectionConfig::WidgetCollectionConfig(RobotGui::WidgetType _type) : WidgetBaseConfig(_type) {}

RobotGui::WidgetCollectionConfig::SharedPtr RobotGui::WidgetCollectionConfig::create(RobotGui::WidgetType _type) {
    return RobotGui::WidgetCollectionConfig::SharedPtr(new WidgetCollectionConfig(_type));
}

RobotGui::WidgetCollectionConfig::SharedPtr RobotGui::WidgetCollectionConfig::create(const std::string &_type) {
    return RobotGui::WidgetCollectionConfig::SharedPtr(new WidgetCollectionConfig(getType(_type)));
}

RobotGui::WidgetCollectionConfig::SharedPtr RobotGui::WidgetCollectionConfig::create() {
    return RobotGui::WidgetCollectionConfig::SharedPtr(new WidgetCollectionConfig(NO_TYPE));
}
//////// Mandatory constructors ////////