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

}

void ThreadedInterface::join() {
    if(std::this_thread::get_id() != thread.get_id()) {
        thread.join();
    }
}
