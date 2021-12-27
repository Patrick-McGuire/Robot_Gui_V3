#include "CoreGui.h"
#include "iostream"
#include "Interface/RandomDataInterface.h"
#include "Interface/WebcamStreamInterface.h"
#include "Interface/FlagCheckerInterface.h"
#include "Theme.h"

//#include "XML/rapidxml/rapidxml_utils.hpp"
//#include "XML/rapidxml/rapidxml_print.hpp"
//#include "XML/rapidxml/rapidxml.hpp"
//
//void test(rapidxml::xml_document<> *doc) {
//    rapidxml::xml_node<> *node = doc->allocate_node(rapidxml::node_element, "a");
//    doc->append_node(node);
//}

int main(int argc, char** argv) {
//    rapidxml::xml_document<> doc;
////    rapidxml::xml_node<> *node = doc.allocate_node(rapidxml::node_element, "Thing");
////    doc.append_node(node);
////    doc.first_node("sdf");
//    test(&doc);
//
//    std::cout << doc << "\n";

    // Create a GUI object
    auto gui = new CoreGui(argc, argv, RobotGui::UPDATE_PERIODIC_AND_ON_POST);

    // Interfaces
    RandomDataInterface randomDataInterface(10);
    WebcamStreamInterface webcamStreamInterface(10);
    FlagCheckerInterface flagCheckerInterface(10);
    gui->addThreadedInterface(&flagCheckerInterface);
    gui->addThreadedInterface(&randomDataInterface);
    gui->addThreadedInterface(&webcamStreamInterface);

    // Run the GUI
    return gui->runGUI();
}
