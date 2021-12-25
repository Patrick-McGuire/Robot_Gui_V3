#ifndef ROBOT_GUI_V3_RANDOMDATAINTERFACE_H
#define ROBOT_GUI_V3_RANDOMDATAINTERFACE_H

#include "ThreadedInterface.h"
#include "../WidgetData.h"
#include "../CoreGUI.h"

/**
 * @class RandomDataInterface
 * Sets random data on a interval
 *
 * @author Patrick McGuire (Patrick-McGuire)
 */
class RandomDataInterface : public ThreadedInterface {
public:
    /**
     * Constructor
     * @param _widgetData datastructures for interface to use
     * @param interval interval on which to update
     */
    RandomDataInterface(CoreGUI *coreGui, int interval);

    /**
     * Sets random data periodically
     */
    void run() override;

private:
    /**
     * Generates a random alpha-numeric string
     * @param length length of string
     * @return random string
     */
    static std::string randomString(size_t length);

    int interval;
};


#endif //ROBOT_GUI_V3_RANDOMDATAINTERFACE_H
