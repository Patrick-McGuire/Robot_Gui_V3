#include <QApplication>
#include <QWidget>
#include "iostream"
#include <QMainWindow>
#include "RobotGUI.h"
#include "CustomWidgets/TextBoxWidget.h"
#include "WidgetInfo.h"
#include <vector>
#include "WidgetData.h"
#include "opencv2/opencv.hpp"
#include "Networking/LocalServer.h"


//using namespace cv;
//int main(int argc, char** argv) {
//    cv::VideoCapture cap;
//    if(!cap.open(0))
//        return 0;
//
//    while (true) {
//        cv::Mat frame;
//        cap >> frame;
//        if( frame.empty() ) break; // end of video stream
//        imshow("this is you, smile! :)", frame);
//        if( cv::waitKey(10) == 27 ) break; // stop capturing by pressing ESC
//    }
//    return 0;
//}

WidgetData widgetData;
int main(int argc, char** argv) {


    QApplication app(argc, argv);
    QMainWindow mainWindow;
    QWidget win;


    std::string test123 = "thisISTH";

    WidgetInfo testInfo(&test123, 45, 50);

    std::vector<std::string> testVector;
    testVector.emplace_back("L1 Tittle");
    testVector.emplace_back("KEY1");

    std::vector<std::string> testVector2;
    testVector2.emplace_back("L2 Tittle");
    testVector2.emplace_back("KEY2");

    std::vector<std::string> testVector3;
    testVector3.emplace_back("L3 Tittle");
    testVector3.emplace_back("KEY3");

    testInfo.lines.push_back(testVector);
    testInfo.lines.push_back(testVector2);
    testInfo.lines.push_back(testVector3);

    widgetData.setInt("KEY1", 100);
    widgetData.setDouble("KEY2", 100);
    widgetData.setString("KEY3", "hi");

    TextBoxWidget test(&win, &testInfo, &widgetData);


    RobotGUI tes123t(&win, &widgetData, &test);

    LocalServer Server(&win, &widgetData, &tes123t);
    Server.StartServer();

    win.show();

    return app.exec();
    return 0;
}
