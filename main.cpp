#include "src/GuiCore.h"
#include "iostream"
#include "src/Interface/RandomDataInterface.h"
#include "src/Interface/WebcamStreamInterface.h"
#include "src/Interface/FlagCheckerInterface.h"
#include "boost/optional/optional.hpp"
#include "vector"

int main(int argc, char** argv) {
    auto gui = new RobotGui::GuiCore(argc, argv);

    // Localhost server interface
//    RobotGui::ServerInterface serverInterface;
//    gui->addInterface(&serverInterface);
//    // Populate keys with random values
    RobotGui::RandomDataInterface randomDataInterface(50);
    gui->addInterface(&randomDataInterface);
//    // Streams the webcam
    RobotGui::WebcamStreamInterface webcamStreamInterface(16);
    gui->addInterface(&webcamStreamInterface);
//    // Prints out any flag raised
    RobotGui::FlagCheckerInterface flagCheckerInterface(100);
    gui->addInterface(&flagCheckerInterface);

    // Run the GUI
    return gui->runGUI();
}
