#include "WebcamStreamInterface.h"
#include "ThreadedInterface.h"

RobotGui::WebcamStreamInterface::WebcamStreamInterface(int _interval) : RobotGui::ThreadedInterface() {
    interval = _interval;
}

void RobotGui::WebcamStreamInterface::run() {
    cv::VideoCapture cap(0);
    if(cap.isOpened()) {
        cv::Mat img;
        cv::Mat img2;
        while (isActive()) {
            cap >> img;
            setImg("1", img);

            img2 = img.clone();
            cv::rectangle(img2, cv::Rect(10, 10, 100, 100), cv::Scalar(0, 0, 255), 2);
            setImg("2", img2);

            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        }
    }
}
