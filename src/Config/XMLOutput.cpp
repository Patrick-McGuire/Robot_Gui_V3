#include "XMLOutput.h"
#include "../../lib/rapidxml/rapidxml.hpp"
#include "../../lib/rapidxml/rapidxml_print.hpp"
#include "../../lib/rapidxml/rapidxml_utils.hpp"


void RobotGui::XMLOutput::output(const char *filename, const RobotGui::WindowConfig_ptr &windowConfig, RobotGui::BaseWidget *firstWidget) {
    rapidxml::xml_document<> doc;
    auto windowNode = createWindowNode(windowConfig, &doc);
    windowNode->append_node(createWidget(&doc, firstWidget));
    write(filename, &doc);
}

rapidxml::xml_node<> *RobotGui::XMLOutput::createWidget(rapidxml::xml_document<> *doc, RobotGui::BaseWidget *widget) {
    rapidxml::xml_node<> *node = doc->allocate_node(rapidxml::node_element, RobotGui::Xml::WIDGET_TAG);
    node->append_attribute(doc->allocate_attribute(RobotGui::Xml::TITLE_ATR, widget->getConfig()->title->c_str()));
    node->append_attribute(doc->allocate_attribute(RobotGui::Xml::DRAGGABLE_ATR, doc->allocate_string(getAttributeString(widget->getConfig()->draggable).c_str())));
    node->append_attribute(doc->allocate_attribute(RobotGui::Xml::STATIC_ATR, doc->allocate_string(getAttributeString(widget->getConfig()->staticPos).c_str())));
    node->append_attribute(doc->allocate_attribute(RobotGui::Xml::X_POS_ATR, doc->allocate_string(getAttributeString(widget->getConfig()->x).c_str())));
    node->append_attribute(doc->allocate_attribute(RobotGui::Xml::Y_POS_ATR, doc->allocate_string(getAttributeString(widget->getConfig()->y).c_str())));


    if(widget->getConfig()->title.is_initialized()) {
        node->append_attribute(doc->allocate_attribute(RobotGui::Xml::TYPE_ATR, widget->getConfig()->getTypeString().c_str()));
    }
    if(widget->getConfig()->backgroundColor.is_initialized()) {
        node->append_attribute(doc->allocate_attribute(RobotGui::Xml::BACKGROUND_COLOR_ATR, widget->getConfig()->backgroundColor->c_str()));
    }
    if(widget->getConfig()->textColor.is_initialized()) {
        node->append_attribute(doc->allocate_attribute(RobotGui::Xml::TEXT_COLOR_ATR, widget->getConfig()->textColor->c_str()));
    }
    if(widget->getConfig()->headerColor.is_initialized()) {
        node->append_attribute(doc->allocate_attribute(RobotGui::Xml::HEADER_COLOR_ATR, widget->getConfig()->headerColor->c_str()));
    }
    if(widget->getConfig()->height.is_initialized()) {
        node->append_attribute(doc->allocate_attribute(RobotGui::Xml::HEIGHT_ATR, doc->allocate_string(getAttributeString(widget->getConfig()->height.get()).c_str())));
    }
    if(widget->getConfig()->width.is_initialized()) {
        node->append_attribute(doc->allocate_attribute(RobotGui::Xml::WIDTH_ATR, doc->allocate_string(getAttributeString(widget->getConfig()->width.get()).c_str())));
    }
    if(widget->getConfig()->source.is_initialized()) {
        node->append_attribute(doc->allocate_attribute(RobotGui::Xml::ID_ATR, widget->getConfig()->source->c_str()));
    }
    widget->outputXML(node, doc);
    return node;
}


rapidxml::xml_node<> *RobotGui::XMLOutput::createWindowNode(const RobotGui::WindowConfig_ptr &windowConfig, rapidxml::xml_document<> *doc) {
    rapidxml::xml_node<> *node = doc->allocate_node(rapidxml::node_element, RobotGui::Xml::WINDOW_TAG);
    doc->append_node(node);
    node->append_attribute(doc->allocate_attribute(RobotGui::Xml::TITLE_ATR, windowConfig->title.c_str()));
    node->append_attribute(doc->allocate_attribute(RobotGui::Xml::THEME_ATR, windowConfig->theme.c_str()));
    node->append_attribute(doc->allocate_attribute(RobotGui::Xml::WIDTH_ATR, doc->allocate_string(getAttributeString(windowConfig->width).c_str())));
    node->append_attribute(doc->allocate_attribute(RobotGui::Xml::HEIGHT_ATR, doc->allocate_string(getAttributeString(windowConfig->height).c_str())));
    return node;
}

void RobotGui::XMLOutput::write(const char *filename, rapidxml::xml_document<> *doc) {
    std::ofstream ofs;
    ofs.open(filename, std::ofstream::out | std::ofstream::trunc);
    ofs << *doc;
    ofs.close();
}

std::string RobotGui::XMLOutput::getAttributeString(int val) {
        if (val == RobotGui::Xml::MAX_CONST_ID) {
            return RobotGui::Xml::MAX_CONST;
        } else if (val == RobotGui::Xml::AUTO_CONST_ID) {
            return RobotGui::Xml::AUTO_CONST;
        } else if (val == RobotGui::Xml::THEME_CONST_ID) {
            return RobotGui::Xml::THEME_CONST;
        } else if (val == RobotGui::Xml::NONE_CONST_ID) {
            return RobotGui::Xml::NONE_CONST;
        }
        return std::to_string(val);
}

std::string RobotGui::XMLOutput::getAttributeString(bool val) {
    return val ? "true" : "false";
}
