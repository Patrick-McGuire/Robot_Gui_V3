#ifndef ROBOT_GUI_V3_XMLOUTPUT_H
#define ROBOT_GUI_V3_XMLOUTPUT_H

#include "../lib/rapidxml/rapidxml.hpp"
#include "../lib/rapidxml/rapidxml_print.hpp"
#include "../lib/rapidxml/rapidxml_utils.hpp"
#include "../RobotGui.h"
#include "../CustomWidgets/BaseWidget.h"

class BaseWidget;

/**
 * @class XML Output
 * Generates a XML file and saves it
 *
 * @author Patrick McGuire (Patrick-McGuire)
 */
class XMLOutput {
public:
    static void output(const char *filename, const RobotGui::WindowConfig_ptr &windowConfig, BaseWidget *firstWidget);

    static rapidxml::xml_node<> *createWidget(rapidxml::xml_document<> *doc, BaseWidget *widget);

private:
    static rapidxml::xml_node<> *createWindowNode(const RobotGui::WindowConfig_ptr &windowConfig, rapidxml::xml_document<> *doc);

    static void write(const char *filename, rapidxml::xml_document<> *doc);

    static std::string getAttributeString(int val);

    static std::string getAttributeString(bool val);

};


#endif //ROBOT_GUI_V3_XMLOUTPUT_H
