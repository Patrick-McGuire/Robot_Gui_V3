#include <QApplication>
#include <QWidget>
#include "iostream"
//#include <map>
#include <QMainWindow>
#include "RobotGUI.h"
#include "CustomWidgets/TextBoxWidget.h"
#include "WidgetInfo.h"
//#include "opencv2/opencv.hpp"
#include <vector>
#include "WidgetData.h"

#include "opencv2/opencv.hpp"

WidgetData widgetData;

//using namespace cv;
//int main(int argc, char** argv)
//{
//    VideoCapture cap;
//    // open the default camera, use something different from 0 otherwise;
//    // Check VideoCapture documentation.
//    if(!cap.open(0))
//        return 0;
//    for(;;)
//    {
//        Mat frame;
//        cap >> frame;
//        if( frame.empty() ) break; // end of video stream
//        imshow("this is you, smile! :)", frame);
//        if( waitKey(10) == 27 ) break; // stop capturing by pressing ESC
//    }
//    // the camera will be closed automatically upon exit
//    // cap.close();
//    return 0;
//}

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
    testVector2.emplace_back("KEY1");

    testInfo.lines.push_back(testVector);
    testInfo.lines.push_back(testVector2);

    widgetData.setInt("KEY1", 100);

    TextBoxWidget test(&win, &testInfo, &widgetData);


    RobotGUI tes123t(&win, &widgetData, &test);

    win.show();

    return app.exec();
    return 0;
}
