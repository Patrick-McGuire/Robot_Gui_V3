#include "GuiCore.h"
#include "iostream"
#include "Interface/RandomDataInterface.h"
#include "Interface/WebcamStreamInterface.h"
#include "Interface/FlagCheckerInterface.h"
#include "Theme.h"
#include <cstdarg>
#include "InternalJson.h"
#include "Interface/ServerInterface.h"

int main(int argc, char** argv) {
    auto gui = new RobotGui::GuiCore(argc, argv);

    // Localhost server interface
//    ServerInterface serverInterface(gui, 1254);
//    gui->addInterface(&serverInterface);
    // Populate keys with random values
    RandomDataInterface randomDataInterface(50);
    gui->addInterface(&randomDataInterface);
    // Streams the webcam
    WebcamStreamInterface webcamStreamInterface(16);
    gui->addInterface(&webcamStreamInterface);
    // Prints out any flag raised
    FlagCheckerInterface flagCheckerInterface(100);
    gui->addInterface(&flagCheckerInterface);

    // Run the GUI
    return gui->runGUI();
}
