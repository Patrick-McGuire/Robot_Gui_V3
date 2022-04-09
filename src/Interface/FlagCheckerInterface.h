#ifndef ROBOT_GUI_V3_FLAGCHECKERINTERFACE_H
#define ROBOT_GUI_V3_FLAGCHECKERINTERFACE_H

#include "ThreadedInterface.h"

namespace RobotGui {
    /**
         * @class FlagCheckerInterface
         * Prints when ever a flag is raised
         *
         * @author Patrick McGuire (Patrick-McGuire)
         */
    class FlagCheckerInterface : public ThreadedInterface {
    public:
        /**
         * Constructor
         * @param interval interval on which to update
         */
        explicit FlagCheckerInterface(int _interval);


        /**
         * Sets random data periodically
         */
        void run() override;

    private:
        int interval;
    };
}


#endif //ROBOT_GUI_V3_FLAGCHECKERINTERFACE_H
