#ifndef ROBOT_GUI_V3_THREADEDINTERFACE_H
#define ROBOT_GUI_V3_THREADEDINTERFACE_H

#include "BaseInterface.h"
#include "thread"
#include "mutex"

namespace RobotGui {
    /**
         * @class ThreadedInterface
         * Extendable Multithreading input to the GUI
         *
         * @author Patrick McGuire (Patrick-McGuire)
         */
    class ThreadedInterface : public RobotGui::BaseInterface {
    public:
        /**
         * Constructor
         */
        explicit ThreadedInterface();

        /**
         * Starts the thread
         */
        void startThread();

        /**
         * Waits for this thread to end
         */
        void join();

    protected:
        /**
         * Derived class run method of the thread
         */
        virtual void run();

    private:

        /**
         * Run method of the thread
         */
        void runThread();

        std::thread *thread;
        std::mutex threadMutex;
    };
}


#endif //ROBOT_GUI_V3_THREADEDINTERFACE_H
