#include "ThreadedInterface.h"

ThreadedInterface::ThreadedInterface(CoreGUI *coreGui) : BaseInterface(coreGui), thread(&ThreadedInterface::startThread, this) {
    coreGui->addThread(&thread);
}

void ThreadedInterface::startThread() {
    std::cout << "Starting Thread\n";
    run();
    std::cout << "Thread Done\n";
}

void ThreadedInterface::run() {
    while (getKeyType("adsf") == WidgetData::none_t) {
        setInt("KEY1", rand() % 20);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void ThreadedInterface::join() {
    thread.join();
}
