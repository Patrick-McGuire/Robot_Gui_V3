#ifndef ROBOT_GUI_V3_XMLOUTPUT_H
#define ROBOT_GUI_V3_XMLOUTPUT_H

#include "../../lib/rapidxml/rapidxml.hpp"
#include "../../lib/rapidxml/rapidxml_print.hpp"
#include "../../lib/rapidxml/rapidxml_utils.hpp"
#include "../RobotGui.h"
#include "../CustomWidgets/BaseStructure/BaseWidget.h"

namespace RobotGui {
    class BaseWidget;

    /**
         * @class XML Output
         * Generates a XML file and saves it
         *
         * @author Patrick McGuire (Patrick-McGuire)
         */
    class XMLOutput {
    public:
        static void output(const char *filename, const WindowConfig_ptr &windowConfig, const WidgetBaseConfig::SharedPtr& firstWidget);

        static rapidxml::xml_node<> *createWidget(rapidxml::xml_document<> *doc, const WidgetBaseConfig::SharedPtr& config);

    private:
        static rapidxml::xml_node<> *createWindowNode(const WindowConfig_ptr &windowConfig, rapidxml::xml_document<> *doc);

        static void write(const char *filename, rapidxml::xml_document<> *doc);

        static std::string getAttributeString(int val);

        static std::string getAttributeString(bool val);

    };
}


#endif //ROBOT_GUI_V3_XMLOUTPUT_H
