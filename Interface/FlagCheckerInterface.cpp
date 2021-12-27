#include "FlagCheckerInterface.h"

FlagCheckerInterface::FlagCheckerInterface(int _interval): ThreadedInterface() {
    interval = _interval;
}

void FlagCheckerInterface::run() {
    while (isActive()) {
        auto flags = getFlagOutput();
        for(auto & flag : *flags) {
            if(flag.second) {
                std::cout << "Flag raised: " << flag.first << std::endl;
                clearOutputFlag(flag.first);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
    }
}
