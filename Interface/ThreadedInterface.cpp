#include "ThreadedInterface.h"

ThreadedInterface::ThreadedInterface(WidgetData *_widgetData) : BaseInterface(_widgetData), thread(&ThreadedInterface::startThread, this) {

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
