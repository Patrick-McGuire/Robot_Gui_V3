#include "CoreGui.h"
#include "iostream"
#include "Interface/RandomDataInterface.h"
#include "Interface/WebcamStreamInterface.h"
#include "Interface/FlagCheckerInterface.h"
#include "Theme.h"


int main(int argc, char** argv) {
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
