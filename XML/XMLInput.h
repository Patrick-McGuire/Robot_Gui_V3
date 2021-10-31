//
// Created by patrick on 10/22/21.
//

#ifndef ROBOT_GUI_V3_XMLINPUT_H
#define ROBOT_GUI_V3_XMLINPUT_H

#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp"
#include "rapidxml/rapidxml_utils.hpp"

class XMLInput {
public:

    /**
     * Parses xml file into internal format
     * @param filename file to parse
     */
    explicit XMLInput(char *filename);
};


#endif //ROBOT_GUI_V3_XMLINPUT_H
