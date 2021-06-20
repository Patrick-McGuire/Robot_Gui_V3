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
#include <QRect>
#include <QDesktopWidget>

std::vector<TabInfo*>* getConfig() {
    auto *tab1Name = new std::string("Tab1");
    auto *tab1 = new TabInfo(tab1Name, false);

    auto *tab2Name = new std::string("Tab2");
    auto *tab2 = new TabInfo(tab2Name, false);

    auto *tab3Name = new std::string("TabCol3");
    auto *tab3 = new TabInfo(tab3Name, true);

    auto *widget1Name = new std::string("Widget1");
    auto *widget2Name = new std::string("Widget2");
    auto *widget1 = new WidgetInfo(widget1Name, 10, 10);
    auto *widget2 = new WidgetInfo(widget2Name, 100, 100);

    auto *line1 = new std::vector<std::string*>;
    auto *line2 = new std::vector<std::string*>;
    auto *line3 = new std::vector<std::string*>;
    auto *a1 = new std::string("Row1");
    auto *aa1 = new std::string("KEY1");
    auto *a2 = new std::string("Row2");
    auto *aa2 = new std::string("KEY2");
    auto *a3 = new std::string("Row3");
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

    tab3->nestedTabsInfo->push_back(tab1);
    tab3->nestedTabsInfo->push_back(tab2);

    auto *ret = new std::vector<TabInfo*>;
    ret->push_back(tab1);
    ret->push_back(tab2);
    ret->push_back(tab3);
    return ret;
}


auto widgetData = new WidgetData();
int main(int argc, char** argv) {
    widgetData->setInt("KEY1", 100);
    widgetData->setDouble("KEY2", 10.1);
    widgetData->setString("KEY3", "hi");

    QApplication app(argc, argv);

    auto mainWindow = new QMainWindow;
    mainWindow->setWindowTitle("Probot Control");

    QRect rec = QApplication::desktop()->availableGeometry();
    mainWindow->resize(rec.width(), rec.height());

    auto *win = new QWidget(mainWindow);


    auto config = getConfig();
    RobotGUI robotGui(win, widgetData, config, mainWindow, rec.width(), rec.height());

    LocalServer Server(win, widgetData, &robotGui);
    Server.StartServer();



    mainWindow->setCentralWidget(win);
    win->show();
    mainWindow->show();
    return app.exec();
}

