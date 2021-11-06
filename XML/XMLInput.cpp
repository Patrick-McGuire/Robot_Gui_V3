//
// Created by patrick on 10/22/21.
//

#include "XMLInput.h"


XMLInput::XMLInput(const char *filename) {
    rapidxml::file<> xmlFile(filename);
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());
    rapidxml::xml_node<> *activeNode = doc.first_node();
    parseNode(activeNode->first_node(), 0);
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
