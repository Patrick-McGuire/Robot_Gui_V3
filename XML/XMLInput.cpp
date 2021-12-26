//
// Created by patrick on 10/22/21.
//

#include "XMLInput.h"

#define strFailed -9123931      // Random

WindowConfig_ptr XMLInput::parse(const char *filename) {
    // Open the file and parse it
    rapidxml::file<> xmlFile(filename);
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());
    rapidxml::xml_node<> *windowNode = doc.first_node();                    // Get the first node, which should be the window node
    // Parse into data structure
    WindowConfig_ptr windowConfig = std::make_shared<WindowConfig>();
    parseWidowNode(windowConfig, windowNode);                               // Gets all attributes from the window tag

    windowConfig->firstChild = parseWidget(windowNode->first_node());

    return windowConfig;
}

WidgetConfig_ptr XMLInput::parseWidget(rapidxml::xml_node<> *node) {
//    auto newWidgetStruct = new WidgetConfig;                    // Struct to return
    WidgetConfig_ptr newWidgetStruct = std::make_shared<WidgetConfig>();
    int tempVal;                                            // Used to keep track of ints parsed from the xml file
    // Parse all basic data into default struct
    for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        std::string attrName = attr->name();                                            // Get the name of the current attribute
        std::string attrVal = attr->value();                                            // Get the value of the current attribute
        // Cases for all non type specific attributes

        if (attrName == XML_TYPE_ATR) {
            newWidgetStruct->type = attrVal;
        } else if (attrName == XML_TITLE_ATR) {
            newWidgetStruct->title = attrVal;
        } else if (attrName == XML_ID_ATR) {
            newWidgetStruct->id = attrVal;
        } else if (attrName == XML_DRAGGABLE_ATTRIBUTE) {
            newWidgetStruct->draggable = (attrVal == XML_TRUE_CAP_CONST || attrVal == XML_TRUE_CONST);       // Default false
        } else if (attrName == XML_STATIC_ATTRIBUTE) {
            newWidgetStruct->staticPos = (attrVal == XML_TRUE_CAP_CONST || attrVal == XML_TRUE_CONST);       // Default false
        } else if (attrName == XML_HIDDEN_ATTRIBUTE) {
            newWidgetStruct->hidden = (attrVal != XML_FALSE_CAP_CONST || attrVal != XML_FALSE_CONST);        // Default true
        } else if (attrName == XML_X_POSITION_ATTRIBUTE) {
            if (isConstant(attrVal)) {                                                         // Check if it is one of a few constant types (ie auto, max, min)
                newWidgetStruct->x = getConstVal(attrVal);
            } else {
                tempVal = safeStoi(attrVal);
                newWidgetStruct->x = tempVal != strFailed ? tempVal : XML_AUTO_CONST_ID;         // If conversion failed return the "auto" id so the GUI can still be created
            }
        } else if (attrName == XML_Y_POSITION_ATTRIBUTE) {
            if (isConstant(attrVal)) {                                                         // Check if it is one of a few constant types (ie auto, max, min)
                newWidgetStruct->y = getConstVal(attrVal);
            } else {
                tempVal = safeStoi(attrVal);
                newWidgetStruct->y = tempVal != strFailed ? tempVal : XML_AUTO_CONST_ID;         // If conversion failed return the "auto" id so the GUI can still be created
            }
        } else if (attrName == XML_HEIGHT_ATR) {
            if (isConstant(attrVal)) {                                                   // Check if it is one of a few constant types (ie auto, max, min)
                newWidgetStruct->height = getConstVal(attrVal);
            } else {
                tempVal = safeStoi(attrVal);
                newWidgetStruct->height = tempVal != strFailed ? tempVal : XML_AUTO_CONST_ID;         // If conversion failed return the "auto" id so the GUI can still be created
            }
        } else if (attrName == XML_WIDTH_ATR) {
            if (isConstant(attrVal)) {                                                   // Check if it is one of a few constant types (ie auto, max, min)
                newWidgetStruct->width = getConstVal(attrVal);
            } else {
                tempVal = safeStoi(attrVal);
                newWidgetStruct->width = tempVal != strFailed ? tempVal : XML_AUTO_CONST_ID;         // If conversion failed return the "auto" id so the GUI can still be created
            }
        } else if (attrName == XML_BACKGROUND_COLOR_ATR) {
            newWidgetStruct->backgroundColor = attrVal;
        } else if (attrName == XML_FOREGROUND_COLOR_ATR) {
            newWidgetStruct->foregroundColor = attrVal;
        } else if (attrName == XML_FONT_ATR) {
            newWidgetStruct->font = attrVal;
        } else if (attrName == XML_RELIEF_ATR) {
            newWidgetStruct->relief = attrVal;
        } else if (attrName == XML_TEXT_COLOR_ATR) {
            newWidgetStruct->textColor = attrVal;
        } else if (attrName == XML_HEADER_COLOR_ATR) {
            newWidgetStruct->headerColor = attrVal;
        } else if (attrName == XML_FONT_SIZE_ATR) {
            if (isConstant(attrVal)) {                                                   // Check if it is one of a few constant types (ie auto, max, min)
                newWidgetStruct->fontSize = getConstVal(attrVal);
            } else {
                tempVal = safeStoi(attrVal);
                newWidgetStruct->fontSize = tempVal != strFailed ? tempVal : XML_AUTO_CONST_ID;         // If conversion failed return the "auto" id so the GUI can still be created
            }
        } else if (attrName == XML_BORDER_WIDTH_ATR) {
            if (isConstant(attrVal)) {                                                   // Check if it is one of a few constant types (ie auto, max, min)
                newWidgetStruct->borderWidth = getConstVal(attrVal);
            } else {
                tempVal = safeStoi(attrVal);
                newWidgetStruct->borderWidth = tempVal != strFailed ? tempVal : XML_AUTO_CONST_ID;         // If conversion failed return the "auto" id so the GUI can still be created
            }
        }
    }
    // Call widget specific methods to finish configuring the struct
    if (newWidgetStruct->type == TEXT_BOX_WIDGET_STRID) {
        TextBoxWidget::parseXml(newWidgetStruct, node);
    } else if (newWidgetStruct->type == VIDEO_WIDGET_STRID) {
        VideoWidget::parseXml(newWidgetStruct, node);
    } else if (newWidgetStruct->type == TAB_WIDGET_STRID) {
        TabWidget::parseXml(newWidgetStruct, node);
    } else if (newWidgetStruct->type == SIMPLE_BUTTON_WIDGET_STRID) {
        SimpleButtonWidget::parseXml(newWidgetStruct, node);
    } else if (newWidgetStruct->type == MULTI_BAR_GRAPH_STRID) {
        MultiBarGraphWidget::parseXml(newWidgetStruct, node);
    }
    setDefaults(newWidgetStruct);
    return newWidgetStruct;
}

void XMLInput::parseWidowNode(const WindowConfig_ptr &windowConfig, rapidxml::xml_node<> *node) {
    int tempVal;
    // Iterate though all attributes
    for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        std::string attrName = attr->name();                                            // Get the name of the current attribute
        std::string attrVal = attr->value();                                            // Get the value of the current attribute
        // Cases
        if (attrName == XML_TITLE_ATR) {
            windowConfig->title = attrVal;
        } else if (attrName == XML_THEME_ATR) {
            windowConfig->theme = attrVal;
        } else if (attrName == XML_HEIGHT_ATR) {
            if (isConstant(attrVal)) {                                                   // Check if it is one of a few constant types (ie auto, max, min)
                windowConfig->height = getConstVal(attrVal);
            } else {
                tempVal = safeStoi(attrVal);
                windowConfig->height = tempVal != strFailed ? tempVal : XML_AUTO_CONST_ID;         // If conversion failed return the "auto" id so the GUI can still be created
            }
        } else if (attrName == XML_WIDTH_ATR) {
            if (isConstant(attrVal)) {                                                   // Check if it is one of a few constant types (ie auto, max, min)
                windowConfig->width = getConstVal(attrVal);
            } else {
                tempVal = safeStoi(attrVal);
                windowConfig->width = tempVal != strFailed ? tempVal : XML_AUTO_CONST_ID;         // If conversion failed return the "auto" id so the GUI can still be created
            }
        }
    }
}

bool XMLInput::isConstant(const std::string &val) {
    return val == XML_MAX_CONST || val == XML_AUTO_CONST;
}

int XMLInput::getConstVal(const std::string &val) {
    if (val == XML_MAX_CONST) {
        return XML_MAX_CONST_ID;
    } else if (val == XML_AUTO_CONST) {
        return XML_AUTO_CONST_ID;
    } else if (val == XML_THEME_CONST) {
        return XML_THEME_CONST_ID;
    } else if (val == XML_NONE_CONST) {
        return XML_NONE_CONST_ID;
    }
    return 0;
}

int XMLInput::safeStoi(const std::string &val) {
    try {
        return std::stoi(val);
    } catch (...) {
        return strFailed;
    }
}

void XMLInput::setDefaults(const WidgetConfig_ptr &widgetConfig) {
    if (widgetConfig->backgroundColor.empty()) {
        widgetConfig->backgroundColor = XML_THEME_CONST;
    }
    if (widgetConfig->textColor.empty()) {
        widgetConfig->textColor = XML_THEME_CONST;
    }
    if (widgetConfig->headerColor.empty()) {
        widgetConfig->headerColor = XML_THEME_CONST;
    }
    if (widgetConfig->relief.empty()) {
        widgetConfig->relief = XML_THEME_CONST;
    }
    if (widgetConfig->font.empty()) {
        widgetConfig->font = XML_THEME_CONST;
    }
    if (widgetConfig->foregroundColor.empty()) {
        widgetConfig->font = XML_THEME_CONST;
    }
}
