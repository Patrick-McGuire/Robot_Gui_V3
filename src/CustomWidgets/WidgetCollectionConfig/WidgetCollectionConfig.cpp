#include "WidgetCollectionConfig.h"
#include "../../Config/XMLInput.h"

//////// Mandatory constructors ////////
RobotGui::WidgetCollectionConfig::WidgetCollectionConfig(WidgetConstants::Type _type) : WidgetBaseConfig(_type) {}

RobotGui::WidgetCollectionConfig::SharedPtr RobotGui::WidgetCollectionConfig::create(WidgetConstants::Type _type) {
    return RobotGui::WidgetCollectionConfig::SharedPtr(new WidgetCollectionConfig(_type));
}

RobotGui::WidgetCollectionConfig::SharedPtr RobotGui::WidgetCollectionConfig::create(const std::string &_type) {
    return RobotGui::WidgetCollectionConfig::SharedPtr(new WidgetCollectionConfig(WidgetConstants::getWidgetType(_type)));
}

RobotGui::WidgetCollectionConfig::SharedPtr RobotGui::WidgetCollectionConfig::create() {
    return RobotGui::WidgetCollectionConfig::SharedPtr(new WidgetCollectionConfig(RobotGui::WidgetConstants::NO_TYPE));
}
//////// Mandatory constructors ////////

void RobotGui::WidgetCollectionConfig::parseXml(rapidxml::xml_node<> *node) {
    for (auto *tab = node->first_node(); tab; tab = tab->next_sibling()) {                           // Iterate over nodes
        std::string tagName = tab->name();
        if (tagName == RobotGui::Xml::TAB_TAG) {
            std::string tabTitle = "No name";
            for (auto *attr = tab->first_attribute(); attr; attr = attr->next_attribute()) {         // Iterate over attributes
                std::string attrName = attr->name();
                std::string attrVal = attr->value();
                if (attrName == RobotGui::Xml::TITLE_ATR) {
                    tabTitle = attrVal;
                }
            }
            tabs.push_back({tabTitle});
            parseTabChildren(tab);
        }
    }
}

void RobotGui::WidgetCollectionConfig::parseTabChildren(rapidxml::xml_node<> *node) {
    // These calls back to XML input to parse the "sub" widgets
    std::vector<RobotGui::WidgetBaseConfig::SharedPtr> widgetsVec;
    for (auto *widget = node->first_node(); widget; widget = widget->next_sibling()) {
        widgetsVec.emplace_back(XMLInput::parseWidget(widget));
    }
    tabs[tabs.size() - 1].widgets = widgetsVec;
}

void RobotGui::WidgetCollectionConfig::outputXML(rapidxml::xml_node<> *node, rapidxml::xml_document<> *doc) {
    for (auto & tabInfo : tabs) {
        rapidxml::xml_node<> *tab = doc->allocate_node(rapidxml::node_element, RobotGui::Xml::TAB_TAG);
        node->append_node(tab);
        tab->append_attribute(doc->allocate_attribute(RobotGui::Xml::TITLE_ATR, tabInfo.name.c_str()));
        for (auto &widget : tabInfo.widgets) {
            tab->append_node(XMLOutput::createWidget(doc, widget));
        }
    }
}
