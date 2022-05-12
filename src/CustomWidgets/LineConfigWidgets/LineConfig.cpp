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
////////   ////////


void RobotGui::LineConfig::parseXml(rapidxml::xml_node<> *node) {
    // Iterate though all lines
    for (auto *line = node->first_node(); line; line = line->next_sibling()) {
        std::string tagName = line->name();
        if (tagName == RobotGui::Xml::LINE_TAG) {
            LineConfig::LineInfo configStruct;
            for (rapidxml::xml_attribute<> *attr = line->first_attribute(); attr; attr = attr->next_attribute()) {
                std::string attrName = attr->name();
                std::string attrVal = attr->value();

                if (attrName == RobotGui::Xml::TYPE_ATR) {
                    configStruct.type = attrVal;
                } else if (attrName == RobotGui::Xml::SOURCE_ATR || attrName == RobotGui::Xml::VALUE_ATR) {
                    configStruct.source = attrVal;
                } else if (attrName == RobotGui::Xml::TITLE_ATR || attrName == RobotGui::Xml::LABEL_ATR) {
                    configStruct.label = attrVal;
                } else if (attrName == RobotGui::Xml::MINIMUM_ATR) {
                    configStruct.min = std::atof(attrVal.c_str());
                } else if (attrName == RobotGui::Xml::MAXIMUM_ATR) {
                    configStruct.max = std::atof(attrVal.c_str());
                } else if (attrName == RobotGui::Xml::COLOR_ATR) {
                    configStruct.color = attrVal;
                }
            }
            lines.push_back(configStruct);
        }
    }
}