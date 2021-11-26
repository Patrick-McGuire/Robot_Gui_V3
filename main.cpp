#include "CoreGUI.h"
#include "iostream"
#include "opencv2/opencv.hpp"

int main(int argc, char** argv) {
    auto gui = new CoreGUI(argc, argv);
    return gui->runGUI();
}

