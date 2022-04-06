#include "FlagCheckerInterface.h"

FlagCheckerInterface::FlagCheckerInterface(int _interval): ThreadedInterface() {
    interval = _interval;
}

void FlagCheckerInterface::run() {
    while (isActive()) {
        auto flags = getFlagOutput();
        auto keys = getFlagOutput()->mapKeys();
        for(auto & flag : keys) {
            if(getFlagOutput(flag)) {
                std::cout << "Flag raised: " << flag << std::endl;
                clearOutputFlag(flag);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
    }
}
