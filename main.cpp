#include "CoreGUI.h"
#include "iostream"
#include "opencv2/opencv.hpp"
#include "thread"
#include "mutex"

//std::mutex globalMutex;
//int test = 0;
//
//void doThing() {
//    while (true) {
//        {
//            std::lock_guard<std::mutex> lockGuard(globalMutex);
//            std::cin >> test;
//            if (test == 5) {
//                break;
//            }
//        }
//        std::this_thread::sleep_for(std::chrono::milliseconds(10));
//    }
//}

int main(int argc, char** argv) {
    auto gui = new CoreGUI(argc, argv);

    return gui->runGUI();
//    std::thread testThread(doThing);
//    int lastTest = 0;
//    while (true) {
//        {
//            std::lock_guard<std::mutex> lockGuard(globalMutex);
//            if (test != lastTest) {
//                std::cout << test << "\n";
//                if (test == 5) {
//                    break;
//                }
//                lastTest = test;
//            }
//        }
//        std::this_thread::sleep_for(std::chrono::milliseconds(10));
//    }
//
//    std::cout << "done\n";
//    testThread.join();
}

