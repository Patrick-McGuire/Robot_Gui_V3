#include "XMLOutput.h"
#include "../../lib/rapidxml/rapidxml.hpp"
#include "../../lib/rapidxml/rapidxml_print.hpp"
#include "../../lib/rapidxml/rapidxml_utils.hpp"


void RobotGui::XMLOutput::output(const char *filename, const RobotGui::WindowConfig_ptr &windowConfig, const WidgetBaseConfig::SharedPtr& firstWidget) {
    rapidxml::xml_document<> doc;
    auto windowNode = createWindowNode(windowConfig, &doc);
    windowNode->append_node(createWidget(&doc, firstWidget));
    write(filename, &doc);
}

rapidxml::xml_node<> *RobotGui::XMLOutput::createWidget(rapidxml::xml_document<> *doc, const WidgetBaseConfig::SharedPtr& config) {
    rapidxml::xml_node<> *node = doc->allocate_node(rapidxml::node_element, RobotGui::Xml::WIDGET_TAG);
    // All required config members
    node->append_attribute(doc->allocate_attribute(RobotGui::Xml::TYPE_ATR, doc->allocate_string(WidgetConstants::getTypeString(config->type).c_str())));
    node->append_attribute(doc->allocate_attribute(RobotGui::Xml::X_POS_ATR, doc->allocate_string(getAttributeString(config->x).c_str())));
    node->append_attribute(doc->allocate_attribute(RobotGui::Xml::Y_POS_ATR, doc->allocate_string(getAttributeString(config->y).c_str())));
    node->append_attribute(doc->allocate_attribute(RobotGui::Xml::HIDDEN_ATR, doc->allocate_string(getAttributeString(config->hidden).c_str())));
    node->append_attribute(doc->allocate_attribute(RobotGui::Xml::DRAGGABLE_ATR, doc->allocate_string(getAttributeString(config->draggable).c_str())));
    node->append_attribute(doc->allocate_attribute(RobotGui::Xml::STATIC_ATR, doc->allocate_string(getAttributeString(config->staticPos).c_str())));
    // All optional config members
    if (config->title.is_initialized()) {  node->append_attribute(doc->allocate_attribute(RobotGui::Xml::TITLE_ATR, config->title->c_str())); }
    if (config->source.is_initialized()) { node->append_attribute(doc->allocate_attribute(RobotGui::Xml::SOURCE_ATR, config->source->c_str())); }
    if (config->height.is_initialized()) { node->append_attribute(doc->allocate_attribute(RobotGui::Xml::HEIGHT_ATR, doc->allocate_string(getAttributeString(config->height.get()).c_str()))); }
    if (config->width.is_initialized()) { node->append_attribute(doc->allocate_attribute(RobotGui::Xml::WIDTH_ATR, doc->allocate_string(getAttributeString(config->width.get()).c_str()))); }
    if (config->size.is_initialized()) { node->append_attribute(doc->allocate_attribute(RobotGui::Xml::SIZE_ATR, doc->allocate_string(getAttributeString(config->size.get()).c_str()))); }
    if (config->min.is_initialized()) { node->append_attribute(doc->allocate_attribute(RobotGui::Xml::MINIMUM_ATR, config->min->c_str())); }
    if (config->max.is_initialized()) { node->append_attribute(doc->allocate_attribute(RobotGui::Xml::MINIMUM_ATR, config->max->c_str())); }
    if (config->range.is_initialized()) { node->append_attribute(doc->allocate_attribute(RobotGui::Xml::RANGE_ATR, doc->allocate_string(std::to_string(config->range.get()).c_str()))); }
    if (config->rowNumber.is_initialized()) { node->append_attribute(doc->allocate_attribute(RobotGui::Xml::ROW_NUMBER_ATR, doc->allocate_string(getAttributeString(config->rowNumber.get()).c_str()))); }
    if (config->columnNumber.is_initialized()) { node->append_attribute(doc->allocate_attribute(RobotGui::Xml::COLUMN_NUMBER_ATR, doc->allocate_string(getAttributeString(config->columnNumber.get()).c_str()))); }
    // Theme based optional members
    if (config->font.is_initialized()) { node->append_attribute(doc->allocate_attribute(RobotGui::Xml::FONT_ATR, config->font->c_str())); }
    if (config->backgroundColor.is_initialized()) { node->append_attribute(doc->allocate_attribute(RobotGui::Xml::BACKGROUND_COLOR_ATR, config->backgroundColor->c_str())); }
    if (config->foregroundColor.is_initialized()) { node->append_attribute(doc->allocate_attribute(RobotGui::Xml::FOREGROUND_COLOR_ATR, config->foregroundColor->c_str())); }
    if (config->relief.is_initialized()) { node->append_attribute(doc->allocate_attribute(RobotGui::Xml::RELIEF_ATR, config->relief->c_str())); }
    if (config->textColor.is_initialized()) { node->append_attribute(doc->allocate_attribute(RobotGui::Xml::TEXT_COLOR_ATR, config->textColor->c_str())); }
    if (config->headerColor.is_initialized()) { node->append_attribute(doc->allocate_attribute(RobotGui::Xml::HEADER_COLOR_ATR, config->headerColor->c_str())); }
//    if (config->borderColor.is_initialized()) { node->append_attribute(doc->allocate_attribute(RobotGui::Xml::BOR, config->borderColor->c_str())); }
    if (config->fontSize.is_initialized()) { node->append_attribute(doc->allocate_attribute(RobotGui::Xml::FONT_SIZE_ATR, doc->allocate_string(getAttributeString(config->fontSize.get()).c_str()))); }
    if (config->borderWidth.is_initialized()) { node->append_attribute(doc->allocate_attribute(RobotGui::Xml::BORDER_WIDTH_ATR, doc->allocate_string(getAttributeString(config->borderWidth.get()).c_str()))); }


    config->outputXML(node, doc);
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
