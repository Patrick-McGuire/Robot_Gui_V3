#include "XMLInput.h"
#include "../CustomWidgets/LineConfigWidgets/LivePlotWidget.h"
#include "../CustomWidgets/BaseStructure/WidgetBaseConfig.h"
#include "../CustomWidgets/LineConfigWidgets/LineConfig.h"
#include "../CustomWidgets/SourceMapConfigWidgets/SourceMapConfig.h"
#include "../CustomWidgets/SourceMapConfigWidgets/MissionStatusWidget.h"
#include "../CustomWidgets/SourceMapConfigWidgets/AttitudeWidget.h"
#include "../CustomWidgets/SourceMapConfigWidgets/ROVStatusWidget.h"
#include "../CustomWidgets/WidgetCollectionConfig/WidgetCollectionConfig.h"
#include "../RobotGui.h"

#define strFailed -9123931      // Random

RobotGui::WindowConfig_ptr RobotGui::XMLInput::parse(const char *filename) {
    // Open the file and parse it
    rapidxml::file<> xmlFile(filename);
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());
    rapidxml::xml_node<> *windowNode = doc.first_node();                    // Get the first node, which should be the window node
    // Parse into data structure
    RobotGui::WindowConfig_ptr windowConfig = std::make_shared<RobotGui::WindowConfig>();
    parseWidowNode(windowConfig, windowNode);                               // Gets all attributes from the window tag

    windowConfig->firstChild = parseWidget(windowNode->first_node());

    return windowConfig;
}

RobotGui::WidgetBaseConfig::SharedPtr RobotGui::XMLInput::parseWidget(rapidxml::xml_node<> *node) {
    RobotGui::WidgetBaseConfig::SharedPtr newWidgetStruct = WidgetBaseConfig::create();
    WidgetConstants::Type type = getWidgetType(node);
    if (type == RobotGui::WidgetConstants::LIVE_PLOT || type == RobotGui::WidgetConstants::TEXT_BOX || type == RobotGui::WidgetConstants::MULTI_BAR_GRAPH) {
        newWidgetStruct = LineConfig::create(type);
    } else if (type == RobotGui::WidgetConstants::MISSION_STATUS || type == RobotGui::WidgetConstants::ROV_STATUS || type == RobotGui::WidgetConstants::ATTITUDE_DISPLAY) {
        newWidgetStruct = SourceMapConfig::create(type);
    } else if (type == RobotGui::WidgetConstants::TAB) {
        newWidgetStruct = WidgetCollectionConfig::create(type);
    } else {
        newWidgetStruct = WidgetBaseConfig::create(type);
    }
    int tempVal;                                            // Used to keep track of ints parsed from the xml file
    // Parse all basic data into default struct
    for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        std::string attrName = attr->name();                                            // Get the name of the current attribute
        std::string attrVal = attr->value();                                            // Get the value of the current attribute
        // Cases for all non type specific attributes

        if (attrName == RobotGui::Xml::TITLE_ATR) {
            newWidgetStruct->title = attrVal;
            newWidgetStruct->title = attrVal;
        } else if (attrName == RobotGui::Xml::ID_ATR) {
            newWidgetStruct->source = attrVal;
        } else if (attrName == RobotGui::Xml::DRAGGABLE_ATR) {
            newWidgetStruct->draggable = (attrVal == RobotGui::Xml::TRUE_CAP_CONST || attrVal == RobotGui::Xml::TRUE_CONST);       // Default false
        } else if (attrName == RobotGui::Xml::STATIC_ATR) {
            newWidgetStruct->staticPos = (attrVal == RobotGui::Xml::TRUE_CAP_CONST || attrVal == RobotGui::Xml::TRUE_CONST);       // Default false
        } else if (attrName == RobotGui::Xml::HIDDEN_ATR) {
            newWidgetStruct->hidden = (attrVal != RobotGui::Xml::FALSE_CAP_CONST || attrVal != RobotGui::Xml::FALSE_CONST);        // Default true
        } else if (attrName == RobotGui::Xml::X_POS_ATR) {
            if (isConstant(attrVal)) {                                                         // Check if it is one of a few constant types (ie auto, max, min)
                newWidgetStruct->x = getConstVal(attrVal);
            } else {
                tempVal = safeStoi(attrVal);
                newWidgetStruct->x = tempVal != strFailed ? tempVal : RobotGui::Xml::AUTO_CONST_ID;         // If conversion failed return the "auto" id so the GUI can still be created
            }
        } else if (attrName == RobotGui::Xml::Y_POS_ATR) {
            if (isConstant(attrVal)) {                                                         // Check if it is one of a few constant types (ie auto, max, min)
                newWidgetStruct->y = getConstVal(attrVal);
            } else {
                tempVal = safeStoi(attrVal);
                newWidgetStruct->y = tempVal != strFailed ? tempVal : RobotGui::Xml::AUTO_CONST_ID;         // If conversion failed return the "auto" id so the GUI can still be created
            }
        } else if (attrName == RobotGui::Xml::HEIGHT_ATR) {
            if (isConstant(attrVal)) {                                                   // Check if it is one of a few constant types (ie auto, max, min)
                newWidgetStruct->height = getConstVal(attrVal);
            } else {
                tempVal = safeStoi(attrVal);
                newWidgetStruct->height = tempVal != strFailed ? tempVal : RobotGui::Xml::AUTO_CONST_ID;         // If conversion failed return the "auto" id so the GUI can still be created
            }
        } else if (attrName == RobotGui::Xml::WIDTH_ATR) {
            if (isConstant(attrVal)) {                                                   // Check if it is one of a few constant types (ie auto, max, min)
                newWidgetStruct->width = getConstVal(attrVal);
            } else {
                tempVal = safeStoi(attrVal);
                newWidgetStruct->width = tempVal != strFailed ? tempVal : RobotGui::Xml::AUTO_CONST_ID;         // If conversion failed return the "auto" id so the GUI can still be created
            }
        } else if (attrName == RobotGui::Xml::ROW_NUMBER_ATR) {
            newWidgetStruct->rowNumber = std::atoi(attrVal.c_str());
        } else if (attrName == RobotGui::Xml::COLUMN_NUMBER_ATR) {
            newWidgetStruct->columnNumber = std::atoi(attrVal.c_str());
        } else if (attrName == RobotGui::Xml::SOURCE_ATTRIBUTE) {
            newWidgetStruct->source = attrVal;
        } else if (attrName == RobotGui::Xml::SIZE_ATR) {
            newWidgetStruct->size = std::atoi(attrVal.c_str());
        } else if (attrName == RobotGui::Xml::MINIMUM_ATR) {
            newWidgetStruct->min = attrVal;
        } else if (attrName == RobotGui::Xml::MAXIMUM_ATR) {
            newWidgetStruct->max = attrVal;
        } else if (attrName == RobotGui::Xml::BACKGROUND_COLOR_ATR) {
            newWidgetStruct->backgroundColor = attrVal;
        } else if (attrName == RobotGui::Xml::FOREGROUND_COLOR_ATR) {
            newWidgetStruct->foregroundColor = attrVal;
        } else if (attrName == RobotGui::Xml::FONT_ATR) {
            newWidgetStruct->font = attrVal;
        } else if (attrName == RobotGui::Xml::RELIEF_ATR) {
            newWidgetStruct->relief = attrVal;
        } else if (attrName == RobotGui::Xml::TEXT_COLOR_ATR) {
            newWidgetStruct->textColor = attrVal;
        } else if (attrName == RobotGui::Xml::HEADER_COLOR_ATR) {
            newWidgetStruct->headerColor = attrVal;
        } else if (attrName == RobotGui::Xml::TRANSPARENT_ATTRIBUTE && CommonFunctions::LowerCaseString(attrVal) == "true") {
            newWidgetStruct->backgroundColor = "none";
            newWidgetStruct->borderColor = "transparent";
        } else if (attrName == RobotGui::Xml::FONT_SIZE_ATR) {
            if (isConstant(attrVal)) {                                                   // Check if it is one of a few constant types (ie auto, max, min)
                newWidgetStruct->fontSize = getConstVal(attrVal);
            } else {
                tempVal = safeStoi(attrVal);
                newWidgetStruct->fontSize = tempVal != strFailed ? tempVal : RobotGui::Xml::AUTO_CONST_ID;         // If conversion failed return the "auto" id so the GUI can still be created
            }
        } else if (attrName == RobotGui::Xml::BORDER_WIDTH_ATR) {
            if (isConstant(attrVal)) {                                                   // Check if it is one of a few constant types (ie auto, max, min)
                newWidgetStruct->borderWidth = getConstVal(attrVal);
            } else {
                tempVal = safeStoi(attrVal);
                newWidgetStruct->borderWidth = tempVal != strFailed ? tempVal : RobotGui::Xml::AUTO_CONST_ID;         // If conversion failed return the "auto" id so the GUI can still be created
            }
        } else if (attrName == RobotGui::Xml::RANGE_ATR) {
            if (isConstant(attrVal)) {                                                   // Check if it is one of a few constant types (ie auto, max, min)
                newWidgetStruct->range = getConstVal(attrVal);
            } else {
                tempVal = safeStoi(attrVal);
                newWidgetStruct->range = tempVal != strFailed ? tempVal : 10;         // If conversion failed return the "auto" id so the GUI can still be created
            }
        }
    }

    newWidgetStruct->parseXml(node);
    return newWidgetStruct;
}

void RobotGui::XMLInput::parseWidowNode(const RobotGui::WindowConfig_ptr &windowConfig, rapidxml::xml_node<> *node) {
    int tempVal;
    // Iterate though all attributes
    for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        std::string attrName = attr->name();                                            // Get the name of the current attribute
        std::string attrVal = attr->value();                                            // Get the value of the current attribute
        // Cases
        if (attrName == RobotGui::Xml::TITLE_ATR) {
            windowConfig->title = attrVal;
        } else if (attrName == RobotGui::Xml::THEME_ATR) {
            windowConfig->theme = attrVal;
        } else if (attrName == RobotGui::Xml::HEIGHT_ATR) {
            if (isConstant(attrVal)) {                                                   // Check if it is one of a few constant types (ie auto, max, min)
                windowConfig->height = getConstVal(attrVal);
            } else {
                tempVal = safeStoi(attrVal);
                windowConfig->height = tempVal != strFailed ? tempVal : RobotGui::Xml::AUTO_CONST_ID;         // If conversion failed return the "auto" id so the GUI can still be created
            }
        } else if (attrName == RobotGui::Xml::WIDTH_ATR) {
            if (isConstant(attrVal)) {                                                   // Check if it is one of a few constant types (ie auto, max, min)
                windowConfig->width = getConstVal(attrVal);
            } else {
                tempVal = safeStoi(attrVal);
                windowConfig->width = tempVal != strFailed ? tempVal : RobotGui::Xml::AUTO_CONST_ID;         // If conversion failed return the "auto" id so the GUI can still be created
            }
        } else if (attrName == RobotGui::Xml::UPDATE_RATE_ATR) {
            if (isConstant(attrVal)) {                                                   // Check if it is one of a few constant types (ie auto, max, min)
                windowConfig->updateRate = getConstVal(attrVal);
            } else {
                tempVal = safeStoi(attrVal);
                windowConfig->updateRate = tempVal != strFailed ? tempVal : RobotGui::Xml::AUTO_CONST_ID;         // If conversion failed return the "auto" id so the GUI can still be created
            }
        }
    }
}

bool RobotGui::XMLInput::isConstant(const std::string &val) {
    return val == RobotGui::Xml::MAX_CONST || val == RobotGui::Xml::AUTO_CONST || val == RobotGui::Xml::THEME_CONST || val == RobotGui::Xml::NONE_CONST
           || val == RobotGui::Xml::CUSTOM_CONST;
}

int RobotGui::XMLInput::getConstVal(const std::string &val) {
    if (val == RobotGui::Xml::MAX_CONST) {
        return RobotGui::Xml::MAX_CONST_ID;
    } else if (val == RobotGui::Xml::AUTO_CONST) {
        return RobotGui::Xml::AUTO_CONST_ID;
    } else if (val == RobotGui::Xml::THEME_CONST) {
        return RobotGui::Xml::THEME_CONST_ID;
    } else if (val == RobotGui::Xml::NONE_CONST) {
        return RobotGui::Xml::NONE_CONST_ID;
    } else if (val == RobotGui::Xml::CUSTOM_CONST) {
        return RobotGui::Xml::CUSTOM_CONST_ID;
    }
    return 0;
}

int RobotGui::XMLInput::safeStoi(const std::string &val) {
    try {
        return std::stoi(val);
    } catch (...) {
        return strFailed;
    }
}


RobotGui::WidgetConstants::Type RobotGui::XMLInput::getWidgetType(rapidxml::xml_node<> *node) {
    for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        std::string attrName = attr->name();                                            // Get the name of the current attribute
        std::string attrVal = attr->value();                                            // Get the value of the current attribute
        // Cases for all non type specific attributes

        if (attrName == RobotGui::Xml::TYPE_ATR) {
            return WidgetConstants::getWidgetType(attrVal);
        }
    }
    return RobotGui::WidgetConstants::NO_TYPE;
}
