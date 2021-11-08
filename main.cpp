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

#include "XML/rapidxml/rapidxml.hpp"
//#include "XML/rapidxml/rapidxml_iterators.hpp"
#include "XML/rapidxml/rapidxml_print.hpp"
#include "XML/rapidxml/rapidxml_utils.hpp"
#include <sstream>
#include <fstream>
#include <QFileDialog>
#include "XML/XMLInput.h"
#include "Configuration/ConfigStructs.h"

void parseXMLTest() {
    struct WindowConfig *aa = XMLInput::parse("/home/patrick/Robot_Gui_V3/ExampleXML/Example2.xml");
    std::cout << aa->title << "\n" << aa->theme << "\n" << aa->width << "\n" << aa->height << "\n";
    for (auto it = begin (aa->firstChild->tabNames); it != aa->firstChild->tabNames.end(); it++) {
        std::cout << it[0] << "\n";
        for(auto j = aa->firstChild->tabWidgets[1].begin(); j != aa->firstChild->tabWidgets[1].end(); j++) {
            std::cout << "\t" << j[0]->title << "\n";
        }
    }
}

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
    std::vector<std::string> line4;
    line1.emplace_back("Row 1");
    line1.emplace_back("KEY1");
    line2.emplace_back("Row 2");
    line2.emplace_back("KEY2");
    line3.emplace_back("Row 3");
    line3.emplace_back("KEY3");
    line4.emplace_back("Row 4");
    line4.emplace_back("KEY4");

    widget1->lines.push_back(line1);
    widget1->lines.push_back(line2);
    widget1->lines.push_back(line3);
    widget1->lines.push_back(line4);
    widget2->lines.push_back(line2);
    widget2->lines.push_back(line3);
    widget2->lines.push_back(line1);
    widget2->lines.push_back(line4);

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

int main(int argc, char** argv) {
    parseXMLTest();
    return 0;
    auto widgetData = new WidgetData();
//    auto widget_data = std::make_shared<WidgetData>();

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

