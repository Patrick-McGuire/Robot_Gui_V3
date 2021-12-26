#ifndef ROBOT_GUI_V3_WEBCAMSTREAMINTERFACE_H
#define ROBOT_GUI_V3_WEBCAMSTREAMINTERFACE_H

#include "ThreadedInterface.h"
#include "opencv2/opencv.hpp"

/**
 * @class WebcamStreamInterface
 * Streams the webcam though the interface
 *
 * @author Patrick McGuire (Patrick-McGuire)
 */
class WebcamStreamInterface : public ThreadedInterface {
public:
    /**
     * Constructor
     * @param interval interval on which to update
     */
    explicit WebcamStreamInterface(int _interval);

    /**
     * Updates the stream periodically
     */
    void run() override;

private:
    int interval;
};


#endif //ROBOT_GUI_V3_WEBCAMSTREAMINTERFACE_H
