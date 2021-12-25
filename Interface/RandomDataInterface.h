#ifndef ROBOT_GUI_V3_RANDOMDATAINTERFACE_H
#define ROBOT_GUI_V3_RANDOMDATAINTERFACE_H

#include "ThreadedInterface.h"
#include "../WidgetData.h"

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

    void run() override;

private:
    int interval;

    static std::string randomString(size_t length);
};


#endif //ROBOT_GUI_V3_RANDOMDATAINTERFACE_H
