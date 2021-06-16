#include <QApplication>
#include <QWidget>
#include "iostream"
//#include <map>
#include <QTimer>
#include <QMainWindow>
#include "RobotGUI.h"

void testFunc() {
    std::cout << "thi";
}

int main(int argc, char** argv) {
//    std::map<std::string, double> testMap;
//    testMap["Thing1"] = 3.25;
//    std::cout << testMap["Thing1"];

    QApplication app(argc, argv);
    QMainWindow mainWindow;
    QWidget win;
//    TextBoxWidget test(&win, "thing1", 40, 50);


    RobotGUI tes123t(&win);

    win.show();

    return app.exec();
}
