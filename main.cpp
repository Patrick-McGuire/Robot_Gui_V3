#include "CoreGUI.h"
#include "iostream"

int main(int argc, char** argv) {
    auto gui = new CoreGUI(argc, argv);
    return gui->runGUI();
}

