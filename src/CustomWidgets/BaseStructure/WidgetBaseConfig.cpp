#include "WidgetBaseConfig.h"
#include "../../RobotGui.h"

RobotGui::WidgetBaseConfig::SharedPtr RobotGui::WidgetBaseConfig::create(const std::string &_type) {
    return RobotGui::WidgetBaseConfig::SharedPtr(new WidgetBaseConfig(WidgetConstants::getWidgetType(_type)));
}

RobotGui::WidgetBaseConfig::SharedPtr RobotGui::WidgetBaseConfig::create(WidgetConstants::Type _type) {
    return RobotGui::WidgetBaseConfig::SharedPtr(new WidgetBaseConfig(_type));
}

RobotGui::WidgetBaseConfig::SharedPtr RobotGui::WidgetBaseConfig::create() {
    return RobotGui::WidgetBaseConfig::SharedPtr(new WidgetBaseConfig(RobotGui::WidgetConstants::NO_TYPE));
}

RobotGui::WidgetBaseConfig::WidgetBaseConfig(WidgetConstants::Type _type) : type(_type) {

}

void RobotGui::WidgetBaseConfig::showEditMenu() {

}

void RobotGui::WidgetBaseConfig::onEdit() {

}

void RobotGui::WidgetBaseConfig::parseXml(rapidxml::xml_node<> *node) {}

void RobotGui::WidgetBaseConfig::outputXML(rapidxml::xml_node<> *node, rapidxml::xml_document<> *doc) {}



