#include "CoreGui.h"
#include "iostream"
#include "Interface/RandomDataInterface.h"
#include "Interface/WebcamStreamInterface.h"
#include "Interface/FlagCheckerInterface.h"
#include "Theme.h"
#include "InternalJson.h"

int main(int argc, char** argv) {
//    InternalJson::SharedPtr json = InternalJson::create();
//    json->setType(InternalJson::map_t);
//
//    json->mapSet("key1", InternalJson::create("test"));
//    json->mapSet("key2", InternalJson::create(5.5));
//
//    InternalJson::SharedPtr  json2 = InternalJson::create();
//    json->mapSet("thing", json2);
//    json2->setType(InternalJson::vector_t);
//
//    json2->vectorAppend(InternalJson::create(false));
//    json2->vectorAppend(InternalJson::create(2));
//    json2->vectorAppend(InternalJson::create("thing is a string"));
//
//    json->print();
//    return 0;

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
