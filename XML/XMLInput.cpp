//
// Created by patrick on 10/22/21.
//

#include "XMLInput.h"


XMLInput::XMLInput(char *filename) {
    rapidxml::file<> xmlFile(filename);
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());
}
