#include "CoreGui.h"
#include "iostream"
#include "Interface/RandomDataInterface.h"
#include "Interface/WebcamStreamInterface.h"
#include "Interface/FlagCheckerInterface.h"
#include "Theme.h"
#include "InternalJson.h"

int main(int argc, char** argv) {
    auto gui = new CoreGui(argc, argv, RobotGui::UPDATE_PERIODIC_AND_ON_POST);

    // Interfaces
    RandomDataInterface randomDataInterface(33);
    WebcamStreamInterface webcamStreamInterface(33);
    FlagCheckerInterface flagCheckerInterface(33);
    gui->addThreadedInterface(&flagCheckerInterface);
    gui->addThreadedInterface(&randomDataInterface);
    gui->addThreadedInterface(&webcamStreamInterface);

    // Run the GUI
    return gui->runGUI();
}
