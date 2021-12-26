#include "ThreadedInterface.h"

ThreadedInterface::ThreadedInterface() : BaseInterface() {
    thread = nullptr;
}

void ThreadedInterface::startThread() {
    std::lock_guard<std::mutex> lockGuard(threadMutex);
    thread = new std::thread(&ThreadedInterface::runThread, this);
}

void ThreadedInterface::runThread() {
    run();
}

void ThreadedInterface::run() {

}

void ThreadedInterface::join() {
    std::lock_guard<std::mutex> lockGuard(threadMutex);
    if(std::this_thread::get_id() != thread->get_id()) {
        thread->join();
    }
}

