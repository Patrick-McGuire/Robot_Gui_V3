#ifndef ROBOT_GUI_V3_XMLINPUT_H
#define ROBOT_GUI_V3_XMLINPUT_H

#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include "iostream"
#include "XMLConstants.h"
#include "../Constants.h"
#include <cstring>
#include "../ConfigStructs.h"
#include "../CustomWidgets/TextBoxWidget.h"
#include "../CustomWidgets/VideoWidget.h"
#include "../CustomWidgets/TabWidget.h"

/**
 * @class XMLInput
 * Static class that parses xml files into the internal configuation format
 *
 * @author Patrick McGuire (Patrick-McGuire)
 */
class XMLInput {
public:

    /**
     * Parses xml file into internal format
     * @param filename file to parse
     */
    static WindowConfig_ptr parse(const char *filename);

    /**
     * Parses a xml node into internal format
     * @param node xml node to parse
     * @return WidgetConfig struct
     */
    static WidgetConfig_ptr parseWidget(rapidxml::xml_node<> *node);

private:
    /**
     * Parses a xml window node into internal format
     * @param windowConfig WindowConfig_ptr to parse into
     * @param node rapidxml node to parse
     */
    static void parseWidowNode(const WindowConfig_ptr& windowConfig, rapidxml::xml_node<> *node);

    /**
     * Checks if a values is a constant defined in XMLConstants.h
     * @param val value to check if it is a constant
     * @return if value is a constant
     */
    static bool isConstant(const std::string& val);

    /**
     * Gets the numerical value for a xml constant
     * @param val value to get numerical constant for
     * @return numerical constant corresponding to val
     */
    static int getConstVal(const std::string& val);

    /**
     * stoi with exception handling, returns large negative number if fails
     * @param val string to parse
     * @return int from string
     */
    static int safeStoi(const std::string& val);

    /**
     * Writes defaults to empty/null attributes of a internal config
     * @param widgetConfig internal config to write defaults to
     */
    static void setDefaults(WidgetConfig_ptr widgetConfig);
};

#endif //ROBOT_GUI_V3_XMLINPUT_H
