#include "CoreGUI.h"
#include "iostream"
#include "Interface/RandomDataInterface.h"
#include "Interface/WebcamStreamInterface.h"


int main(int argc, char** argv) {
    // Create a GUI object
    auto gui = new CoreGUI(argc, argv, UPDATE_PERIODIC_ON_POST);

    // Interfaces
    RandomDataInterface randomDataInterface(10);
    WebcamStreamInterface webcamStreamInterface(10);
    gui->addThreadedInterface(&randomDataInterface);
    gui->addThreadedInterface(&webcamStreamInterface);

    // Run the GUI
    return gui->runGUI();
}
