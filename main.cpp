#include "CoreGUI.h"
#include "iostream"
#include "opencv2/opencv.hpp"
#include "thread"
#include "mutex"
#include "Interface/ThreadedInterface.h"


int main(int argc, char** argv) {
    auto gui = new CoreGUI(argc, argv);
    ThreadedInterface threadedInterface(gui->getWidgetData());
    return gui->runGUI();
}

