#ifndef ROBOT_GUI_V3_THREADEDINTERFACE_H
#define ROBOT_GUI_V3_THREADEDINTERFACE_H

#include "BaseInterface.h"
#include "thread"

/**
 * @class ThreadedInterface
 * Extendable Multithreading input to the GUI
 *
 * @author Patrick McGuire (Patrick-McGuire)
 */
class ThreadedInterface : public BaseInterface {
public:
    /**
     * Constructor
     * @param coreGui gui object to interface with
     */
    explicit ThreadedInterface(CoreGUI *coreGui);

    /**
     * Waits for this thread to end
     * No memory control here, but nothing will happen if called from this thread
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
    void startThread();

    std::thread thread;
};


#endif //ROBOT_GUI_V3_THREADEDINTERFACE_H
