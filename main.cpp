#include "src/GuiCore.h"
#include "iostream"
#include "src/Interface/RandomDataInterface.h"
#include "src/Interface/WebcamStreamInterface.h"
#include "src/Interface/FlagCheckerInterface.h"

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
