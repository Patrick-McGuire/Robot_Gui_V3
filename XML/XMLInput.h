//
// Created by patrick on 10/22/21.
//

#ifndef ROBOT_GUI_V3_XMLINPUT_H
#define ROBOT_GUI_V3_XMLINPUT_H

#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include "iostream"
#include "XMLConstants.h"
#include "../Constants.h"
#include <cstring>
#include "../Configuration/ConfigStructs.h"
#include "../CustomWidgets/TextBoxWidget.h"
#include "../CustomWidgets/VideoWidget.h"
#include "../CustomWidgets/TabWidget.h"

class XMLInput {
public:

    /**
     * Parses xml file into internal format
     * @param filename file to parse
     */
    static WindowConfig *parse(const char *filename);

    /**
     * Parses a xml node into internal format
     * @param node xml node to parse
     * @return WidgetConfig struct
     */
    static WidgetConfig *parseWidget(rapidxml::xml_node<> *node);

private:
    static void parseWidowNode(struct WindowConfig *windowConfig, rapidxml::xml_node<> *node);

    static bool isConstant(const std::string& val);
    static int getConstVal(const std::string& val);
    static int safeStoi(const std::string& val);
};


#endif //ROBOT_GUI_V3_XMLINPUT_H
