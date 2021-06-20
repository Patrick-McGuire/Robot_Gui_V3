#include <QApplication>
#include <QWidget>
#include "iostream"
#include <QMainWindow>
#include "RobotGUI.h"
#include "CustomWidgets/TextBoxWidget.h"
#include <vector>
#include "WidgetData.h"
#include "opencv2/opencv.hpp"
#include "Networking/LocalServer.h"
#include "Configuration/TabInfo.h"
#include "Configuration/WidgetInfo.h"

std::vector<TabInfo*>* getConfig() {
    auto *tab1Name = new std::string("Tab1");
    auto *tab1 = new TabInfo(tab1Name, false);

    auto *tab2Name = new std::string("Tab2");
    auto *tab2 = new TabInfo(tab2Name, false);

    auto *widget1Name = new std::string("Widget1");
    auto *widget2Name = new std::string("Widget2");
    auto *widget1 = new WidgetInfo(widget1Name, 10, 10);
    auto *widget2 = new WidgetInfo(widget2Name, 100, 100);

    auto *line1 = new std::vector<std::string*>;
    auto *line2 = new std::vector<std::string*>;
    auto *line3 = new std::vector<std::string*>;
    auto *a1 = new std::string("Row1");
    auto *aa1 = new std::string("KEY1");
    auto *a2 = new std::string("Row1");
    auto *aa2 = new std::string("KEY2");
    auto *a3 = new std::string("Row1");
    auto *aa3 = new std::string("KEY3");
    line1->push_back(a1);
    line1->push_back(aa1);
    line2->push_back(a2);
    line2->push_back(aa2);
    line3->push_back(a3);
    line3->push_back(aa3);
    widget1->lines->push_back(line1);
    widget1->lines->push_back(line2);
    widget1->lines->push_back(line3);
    widget2->lines->push_back(line2);
    widget2->lines->push_back(line3);
    widget2->lines->push_back(line1);


    tab1->widgetsInfo->push_back(widget1);
    tab1->widgetsInfo->push_back(widget2);

    auto *ret = new std::vector<TabInfo*>;
    ret->push_back(tab1);
    ret->push_back(tab2);
    return ret;
}


auto widgetData = new WidgetData();
int main(int argc, char** argv) {
    widgetData->setInt("KEY1", 100);
    widgetData->setDouble("KEY2", 10.1);
    widgetData->setString("KEY3", "hi");

    QApplication app(argc, argv);
    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Window");

    auto *win = new QWidget(&mainWindow);


//    std::vector<TabInfo*> *config;
    auto config = getConfig();
    RobotGUI robotGui(win, widgetData, config);

    LocalServer Server(win, widgetData, &robotGui);
    Server.StartServer();



    mainWindow.setCentralWidget(win);
    win->show();
    mainWindow.show();
    return app.exec();
}

//QApplication app(argc, argv);
//QMainWindow mainWindow;
//QWidget win;
//
//
//std::string test123 = "thisISTH";
//
//WidgetInfo testInfo(&test123, 45, 50);
//
//std::vector<std::string> testVector;
//testVector.emplace_back("L1 Tittle");
//testVector.emplace_back("KEY1");
//
//std::vector<std::string> testVector2;
//testVector2.emplace_back("L2 Tittle");
//testVector2.emplace_back("KEY2");
//
//std::vector<std::string> testVector3;
//testVector3.emplace_back("L3 Tittle");
//testVector3.emplace_back("KEY3");
//
//testInfo.lines.push_back(testVector);
//testInfo.lines.push_back(testVector2);
//testInfo.lines.push_back(testVector3);
//
//widgetData.setInt("KEY1", 100);
//widgetData.setDouble("KEY2", 100);
//widgetData.setString("KEY3", "hi");
//
//TextBoxWidget test(&win, &testInfo, &widgetData);
//
//RobotGUI tes123t(&win, &widgetData, &test);
//
//LocalServer Server(&win, &widgetData, &tes123t);
//Server.StartServer();
//
//win.show();
//return app.exec();
