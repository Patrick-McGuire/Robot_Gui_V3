#include "CoreGUI.h"
#include "iostream"
#include "opencv2/opencv.hpp"
#include "thread"
#include "mutex"
#include "Interface/ThreadedInterface.h"
#include "Interface/RandomDataInterface.h"


int main(int argc, char** argv) {
    auto gui = new CoreGUI(argc, argv);
    RandomDataInterface randomDataInterface(10);
    gui->addThreadedInterface(&randomDataInterface);
    return gui->runGUI();
}

