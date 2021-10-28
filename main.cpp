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
#include "Constants.h"

std::vector<TabInfo*>* getConfig() {
    auto *tab1 = new TabInfo("Tab1", false);
    auto *tab2 = new TabInfo("Tab2", false);
    auto *tab3 = new TabInfo("TabCol3", true);

    auto *widget1 = new WidgetInfo("Widget1", textBoxWidgetSTRID, 10, 10);
    auto *widget2 = new WidgetInfo("Widget2", textBoxWidgetSTRID, 100, 100);
    auto *widget3 = new WidgetInfo("Widget3", videoWidgetSTRID, 200, 200);
    auto *widget4 = new WidgetInfo("Widget4", videoWidgetSTRID, 400, 400);
    widget3->videoId = "1";
    widget4->videoId = "2";

    std::vector<std::string> line1;
    std::vector<std::string> line2;
    std::vector<std::string> line3;
    line1.emplace_back("Row 1");
    line1.emplace_back("KEY1");
    line2.emplace_back("Row 2");
    line2.emplace_back("KEY2");
    line3.emplace_back("Row 3");
    line3.emplace_back("KEY3");

    widget1->lines.push_back(line1);
    widget1->lines.push_back(line2);
    widget1->lines.push_back(line3);
    widget2->lines.push_back(line2);
    widget2->lines.push_back(line3);
    widget2->lines.push_back(line1);

    tab1->widgetsInfo->push_back(widget1);
    tab1->widgetsInfo->push_back(widget2);
    tab1->widgetsInfo->push_back(widget3);
    tab1->widgetsInfo->push_back(widget4);

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
//    mainWindow->resize(600, 600);
    auto *win = new QWidget(mainWindow);
//    win->resize(mainWindow->width(), mainWindow->height());

    auto config = getConfig();
    RobotGUI robotGui(win, widgetData, config, mainWindow, rec.width(), rec.height());

    LocalServer Server(win, widgetData, &robotGui);
    Server.StartServer();



    mainWindow->setCentralWidget(win);
    win->show();
    mainWindow->show();
    return app.exec();
}

