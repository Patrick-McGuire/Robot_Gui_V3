#include "CoreGUI.h"

int main(int argc, char** argv) {
    auto gui = new CoreGUI(argc, argv);
    return gui->runGUI();
}

