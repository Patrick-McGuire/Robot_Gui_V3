//
// Created by patrick on 10/22/21.
//

#include "XMLInput.h"
#define strFailed -9123931

WindowConfig *XMLInput::parse(const char *filename) {
    // Open the file and parse it
    rapidxml::file<> xmlFile(filename);
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());
    rapidxml::xml_node<> *windowNode = doc.first_node();                    // Get the first node, which should be the window node
    // Parse into data structure
    auto windowConfig = new WindowConfig;                                   // Window config struct
    parseWidowNode(windowConfig, windowNode);                               // Gets all attributes from the window tag

    windowConfig->firstChild = parseWidget(windowNode->first_node());

    return windowConfig;
}

WidgetConfig *XMLInput::parseWidget(rapidxml::xml_node<> *node) {
    auto newWidgetStruct = new WidgetConfig;                    // Struct to return
    int tempVal = 0;                                            // Used to keep track of ints parsed from the xml file
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
        }
    }
    // Call widget specific methods to finish configuring the struct
    if(newWidgetStruct->type == textBoxWidgetSTRID) {
        TextBoxWidget::parseXml(newWidgetStruct, node);
    } else if(newWidgetStruct->type == videoWidgetSTRID) {
        VideoWidget::parseXml(newWidgetStruct, node);
    }
    return newWidgetStruct;
}

void XMLInput::parseWidowNode(struct WindowConfig *windowConfig, rapidxml::xml_node<> *node) {
    int tempVal = 0;
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
