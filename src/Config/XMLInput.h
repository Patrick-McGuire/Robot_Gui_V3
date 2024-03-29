    #ifndef ROBOT_GUI_V3_XMLINPUT_H
#define ROBOT_GUI_V3_XMLINPUT_H

#include "../../lib/rapidxml/rapidxml.hpp"
#include "../../lib/rapidxml/rapidxml_print.hpp"
#include "../../lib/rapidxml/rapidxml_utils.hpp"
#include "iostream"
#include "../RobotGui.h"
#include <cstring>
#include "../CustomWidgets/LineConfigWidgets/TextBoxWidget.h"
#include "../CustomWidgets/VideoWidget.h"
#include "../CustomWidgets/WidgetCollectionConfig/TabWidget.h"
#include "../CustomWidgets/SimpleButtonWidget.h"
#include "../CustomWidgets/LineConfigWidgets/MultiBarGraphWidget.h"

    namespace RobotGui {
    /**
         * @class XMLInput
         * Static class that parses xml files into the internal configuration format
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
        static WidgetBaseConfig::SharedPtr parseWidget(rapidxml::xml_node<> *node);

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

        static WidgetConstants::Type getWidgetType(rapidxml::xml_node<> *node);
    };
}

#endif //ROBOT_GUI_V3_XMLINPUT_H
