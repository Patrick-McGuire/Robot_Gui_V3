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

void RobotGui::SourceMapConfig::parseXml(rapidxml::xml_node<> *node) {
    for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        std::string attrName = attr->name();                                            // Get the name of the current attribute
        std::string attrVal = attr->value();                                            // Get the value of the current attribute
        if (attrName.find("Source") != std::string::npos) {
            sourceMap[attrName] = attrVal;
        }
    }
}