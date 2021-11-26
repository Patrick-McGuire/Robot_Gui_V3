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
    for(rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        std::string attrName = attr->name();                                            // Get the name of the current attribute
        std::string attrVal = attr->value();                                            // Get the value of the current attribute
        // Cases for all non type specific attributes

        if(attrName == xmlTypeATR) {
            newWidgetStruct->type = attrVal;
        } else if(attrName == xmlTitleATR) {
            newWidgetStruct->title = attrVal;
        } else if(attrName == xmlIdATR) {
            newWidgetStruct->id = attrVal;
        } else if(attrName == xmlDraggableATR) {
            newWidgetStruct->draggable = (attrVal == xmlTrueCapConst || attrVal == xmlTrueConst);       // Default false
        }  else if(attrName == xmlStaticATR) {
            newWidgetStruct->staticPos = (attrVal == xmlTrueCapConst || attrVal == xmlTrueConst);       // Default false
        } else if(attrName == xmlHiddenATR) {
            newWidgetStruct->hidden = (attrVal != xmlFalseCapConst || attrVal != xmlFalseConst);        // Default true
        } else if(attrName == xmlXPosATR) {
            if(isConstant(attrVal)) {                                                         // Check if it is one of a few constant types (ie auto, max, min)
                newWidgetStruct->x = getConstVal(attrVal);
            } else {
                tempVal = safeStoi(attrVal);
                newWidgetStruct->x = tempVal != strFailed ? tempVal : xmlAutoConstID;         // If conversion failed return the "auto" id so the GUI can still be created
            }
        } else if(attrName == xmlYPosATR) {
            if(isConstant(attrVal)) {                                                         // Check if it is one of a few constant types (ie auto, max, min)
                newWidgetStruct->y = getConstVal(attrVal);
            } else {
                tempVal = safeStoi(attrVal);
                newWidgetStruct->y = tempVal != strFailed ? tempVal : xmlAutoConstID;         // If conversion failed return the "auto" id so the GUI can still be created
            }
        } else if(attrName == xmlHeightATR) {
            if(isConstant(attrVal)) {                                                   // Check if it is one of a few constant types (ie auto, max, min)
                newWidgetStruct->height = getConstVal(attrVal);
            } else {
                tempVal = safeStoi(attrVal);
                newWidgetStruct->height = tempVal != strFailed ? tempVal : xmlAutoConstID;         // If conversion failed return the "auto" id so the GUI can still be created
            }
        } else if(attrName == xmlWidthATR) {
            if(isConstant(attrVal)) {                                                   // Check if it is one of a few constant types (ie auto, max, min)
                newWidgetStruct->width = getConstVal(attrVal);
            } else {
                tempVal = safeStoi(attrVal);
                newWidgetStruct->width = tempVal != strFailed ? tempVal : xmlAutoConstID;         // If conversion failed return the "auto" id so the GUI can still be created
            }
        } else if(attrName == xmlBackgroundColorATR) {
            newWidgetStruct->backgroundColor = attrVal;
        } else if(attrName == xmlForegroundColorATR) {
            newWidgetStruct->foregroundColor = attrVal;
        } else if(attrName == xmlFontATR) {
            newWidgetStruct->font = attrVal;
        } else if(attrName == xmlReliefATR) {
            newWidgetStruct->relief = attrVal;
        } else if(attrName == xmlTextColorATR) {
            newWidgetStruct->textColor = attrVal;
        } else if(attrName == xmlHeaderColorATR) {
            newWidgetStruct->headerColor = attrVal;
        } else if(attrName == xmlFontSizeATR) {
            if(isConstant(attrVal)) {                                                   // Check if it is one of a few constant types (ie auto, max, min)
                newWidgetStruct->fontSize = getConstVal(attrVal);
            } else {
                tempVal = safeStoi(attrVal);
                newWidgetStruct->fontSize = tempVal != strFailed ? tempVal : xmlAutoConstID;         // If conversion failed return the "auto" id so the GUI can still be created
            }
        } else if(attrName == xmlBorderWidthATR) {
            if(isConstant(attrVal)) {                                                   // Check if it is one of a few constant types (ie auto, max, min)
                newWidgetStruct->borderWidth = getConstVal(attrVal);
            } else {
                tempVal = safeStoi(attrVal);
                newWidgetStruct->borderWidth = tempVal != strFailed ? tempVal : xmlAutoConstID;         // If conversion failed return the "auto" id so the GUI can still be created
            }
        }
    }
    // Call widget specific methods to finish configuring the struct
    if(newWidgetStruct->type == textBoxWidgetSTRID) {
        TextBoxWidget::parseXml(newWidgetStruct, node);
    } else if(newWidgetStruct->type == videoWidgetSTRID) {
        VideoWidget::parseXml(newWidgetStruct, node);
    } else if(newWidgetStruct->type == tabWidgetSTRID) {
        TabWidget::parseXml(newWidgetStruct, node);
    } else if(newWidgetStruct->type == SIMPLE_BUTTON_WIDGET_STRID) {
        SimpleButtonWidget::parseXml(newWidgetStruct, node);
    }
    setDefaults(newWidgetStruct);
    return newWidgetStruct;
}

void XMLInput::parseWidowNode(const WindowConfig_ptr& windowConfig, rapidxml::xml_node<> *node) {
    int tempVal;
    // Iterate though all attributes
    for(rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        std::string attrName = attr->name();                                            // Get the name of the current attribute
        std::string attrVal = attr->value();                                            // Get the value of the current attribute
        // Cases
        if(attrName == xmlTitleATR) {
            windowConfig->title = attrVal;
        } else if(attrName == xmlThemeATR) {
            windowConfig->theme = attrVal;
        } else if(attrName == xmlHeightATR) {
            if(isConstant(attrVal)) {                                                   // Check if it is one of a few constant types (ie auto, max, min)
                windowConfig->height = getConstVal(attrVal);
            } else {
                tempVal = safeStoi(attrVal);
                windowConfig->height = tempVal != strFailed ? tempVal : xmlAutoConstID;         // If conversion failed return the "auto" id so the GUI can still be created
            }
        } else if(attrName == xmlWidthATR) {
            if(isConstant(attrVal)) {                                                   // Check if it is one of a few constant types (ie auto, max, min)
                windowConfig->width = getConstVal(attrVal);
            } else {
                tempVal = safeStoi(attrVal);
                windowConfig->width = tempVal != strFailed ? tempVal : xmlAutoConstID;         // If conversion failed return the "auto" id so the GUI can still be created
            }
        }
    }
}

bool XMLInput::isConstant(const std::string& val) {
    return val == xmlMaxConst || val == xmlAutoConst;
}

int XMLInput::getConstVal(const std::string& val) {
    if(val == xmlMaxConst) {
        return xmlMaxConstID;
    } else if(val == xmlAutoConst) {
        return xmlAutoConstID;
    } else if(val == xmlThemeConst) {
        return xmlThemeConstID;
    } else if(val == xmlNoneConst) {
        return xmlNoneConstID;
    }
    return 0;
}

int XMLInput::safeStoi(const std::string &val) {
    try {
        return std::stoi(val);
    } catch(...) {
        return strFailed;
    }
}

void XMLInput::setDefaults(const WidgetConfig_ptr& widgetConfig) {
    if(widgetConfig->backgroundColor.empty()) {
        widgetConfig->backgroundColor = xmlThemeConst;
    }
    if(widgetConfig->textColor.empty()) {
        widgetConfig->textColor = xmlThemeConst;
    }
    if(widgetConfig->headerColor.empty()) {
        widgetConfig->headerColor = xmlThemeConst;
    }
    if(widgetConfig->relief.empty()) {
        widgetConfig->relief = xmlThemeConst;
    }
    if(widgetConfig->font.empty()) {
        widgetConfig->font = xmlThemeConst;
    }
    if(widgetConfig->foregroundColor.empty()) {
        widgetConfig->font = xmlThemeConst;
    }
}
