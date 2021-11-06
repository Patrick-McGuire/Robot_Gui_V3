//
// Created by patrick on 10/22/21.
//

#include "XMLInput.h"

WindowConfig *XMLInput::parse(const char *filename) {
    // Open the file and parse it
    rapidxml::file<> xmlFile(filename);
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());
    rapidxml::xml_node<> *windowNode = doc.first_node();                    // Get the first node, which should be the window node
    // Parse into data structure
    auto windowConfig = new WindowConfig;
    parseWidowNode(windowConfig, windowNode);


    return windowConfig;
}

void XMLInput::parseWidowNode(struct WindowConfig *windowConfig, rapidxml::xml_node<> *node) {
    rapidxml::xml_attribute<> *attr = node->first_attribute();                          // Get an attribute object to iterate though
    int tempVal = 0;
    // Iterate though all attributes
    while (attr) {
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
                windowConfig->height = tempVal != 0 ? tempVal : xmlAutoConstID;         // If conversion failed return the "auto" id so the GUI can still be created
            }
        } else if(attrName == xmlWidthATR) {
            if(isConstant(attrVal)) {                                                   // Check if it is one of a few constant types (ie auto, max, min)
                windowConfig->width = getConstVal(attrVal);
            } else {
                tempVal = safeStoi(attrVal);
                windowConfig->width = tempVal != 0 ? tempVal : xmlAutoConstID;         // If conversion failed return the "auto" id so the GUI can still be created
            }
        }
        attr = attr->next_attribute();                                      // Iterate to the next attribute
    }
}

void XMLInput::parseNode(rapidxml::xml_node<> *node, int tabNum) {
    while (node) {
        rapidxml::xml_attribute<> *attr = node->first_attribute();
        for(int i = 0; i < tabNum; i++) { std::cout << "\t"; }
        std::cout << node->name() << ":\n";
        if(strcmp(node->name(), xmlWidgetCollectionTag) == 0) {
            while (attr) {
                for(int i = 0; i < tabNum; i++) { std::cout << "\t"; }
                std::cout << "\t" << attr->name() << " : " << attr->value() << "\n";
                attr = attr->next_attribute();
            }
        } else if(strcmp(node->name(), xmlWidgetTag) == 0) {
            while (attr) {
                for(int i = 0; i < tabNum; i++) { std::cout << "\t"; }
                std::cout << "\t" << attr->name() << " : " << attr->value() << "\n";
                attr = attr->next_attribute();
            }
        }
        std::cout << "\n";
        parseNode(node->first_node(), tabNum + 2);
        node = node->next_sibling();
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
        return 0;
    }
}
