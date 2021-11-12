#include <QApplication>
#include <QWidget>
#include "iostream"
#include <QMainWindow>
#include "RobotGUI.h"
#include <vector>
#include "WidgetData.h"
#include "Networking/LocalServer.h"
#include <QRect>
#include <QDesktopWidget>
#include "Constants.h"


#include "experimental/filesystem"
#include <iostream>
#include <fstream>

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include "XML/AppConfig.h"

void test() {
    auto a = new AppConfig;
    a->parseConfig();
    std::cout << a->getDefaultXmlPath()<< "\n";
    a->setDefaultXmlPath(".F.FF");
    a->setConfig();
    delete a;

    auto aa = new AppConfig;
    aa->parseConfig();
    std::cout << aa->getDefaultXmlPath() << "\n";
}

int main(int argc, char** argv) {
    test();
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
    win->resize(mainWindow->width(), mainWindow->height());

    RobotGUI robotGui(win, widgetData, nullptr, mainWindow, rec.width(), rec.height());

    LocalServer Server(win, widgetData, &robotGui);
    Server.StartServer();



    mainWindow->setCentralWidget(win);
    win->show();
    mainWindow->show();
    return app.exec();
}

