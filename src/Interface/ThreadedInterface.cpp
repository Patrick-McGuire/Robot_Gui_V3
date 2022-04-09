#include "ThreadedInterface.h"
#include "BaseInterface.h"

RobotGui::ThreadedInterface::ThreadedInterface() : RobotGui::BaseInterface() {
    thread = nullptr;
}

void RobotGui::ThreadedInterface::startThread() {
    std::lock_guard<std::mutex> lockGuard(threadMutex);
    thread = new std::thread(&ThreadedInterface::runThread, this);
}

void RobotGui::ThreadedInterface::runThread() {
    run();
}

void RobotGui::ThreadedInterface::run() {

}

void RobotGui::ThreadedInterface::join() {
    std::lock_guard<std::mutex> lockGuard(threadMutex);
    if(std::this_thread::get_id() != thread->get_id()) {
        thread->join();
    }
}

