#include "LineConfig.h"

//////// Mandatory constructors ////////
RobotGui::LineConfig::LineConfig(WidgetConstants::Type _type) : WidgetBaseConfig(_type) {}

RobotGui::LineConfig::SharedPtr RobotGui::LineConfig::create(WidgetConstants::Type _type) {
    return RobotGui::LineConfig::SharedPtr(new LineConfig(_type));
}

RobotGui::LineConfig::SharedPtr RobotGui::LineConfig::create(const std::string &_type) {
    return RobotGui::LineConfig::SharedPtr(new LineConfig(WidgetConstants::getWidgetType(_type)));
}

RobotGui::LineConfig::SharedPtr RobotGui::LineConfig::create() {
    return RobotGui::LineConfig::SharedPtr(new LineConfig(RobotGui::WidgetConstants::NO_TYPE));
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

void RobotGui::LineConfig::outputXML(rapidxml::xml_node<> *node, rapidxml::xml_document<> *doc) {
    for (auto &lineInfo: lines) {
        // Allocate line node
        rapidxml::xml_node<> *line = doc->allocate_node(rapidxml::node_element, RobotGui::Xml::LINE_TAG);
        node->append_node(line);
        // Add line attributes
        line->append_attribute(doc->allocate_attribute(RobotGui::Xml::LABEL_ATR, lineInfo.label.c_str()));
        line->append_attribute(doc->allocate_attribute(RobotGui::Xml::VALUE_ATR, lineInfo.source.c_str()));
        if(lineInfo.color.is_initialized()) {
            line->append_attribute(doc->allocate_attribute(RobotGui::Xml::COLOR_ATR, lineInfo.color->c_str()));
        }
        if(lineInfo.type.is_initialized()) {
            line->append_attribute(doc->allocate_attribute(RobotGui::Xml::TYPE_ATR, lineInfo.type->c_str()));
        }
        if(lineInfo.min.is_initialized()) {
            line->append_attribute(doc->allocate_attribute(RobotGui::Xml::MINIMUM_ATR, doc->allocate_string(std::to_string(lineInfo.min.get()).c_str())));
        }
        if(lineInfo.max.is_initialized()) {
            line->append_attribute(doc->allocate_attribute(RobotGui::Xml::MAXIMUM_ATR, doc->allocate_string(std::to_string(lineInfo.max.get()).c_str())));
        }
    }
}
