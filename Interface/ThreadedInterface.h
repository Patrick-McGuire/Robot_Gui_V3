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
     * @param _widgetData
     */
    explicit ThreadedInterface(CoreGUI *coreGui);

    /**
     * Waits for this thread to end
     */
    void join();

protected:
    virtual void run();

private:
    std::thread thread;
    void startThread();
};


#endif //ROBOT_GUI_V3_THREADEDINTERFACE_H
