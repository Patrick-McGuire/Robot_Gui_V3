//
// Created by patrick on 11/12/21.
//

#ifndef ROBOT_GUI_V3_MENU_H
#define ROBOT_GUI_V3_MENU_H
#include <string>
#include "QWidget"
#include "QMouseEvent"
#include "QMenuBar"
#include "iostream"
#include "XML/AppConfig.h"

class Menu : public QWidget {
Q_OBJECT
public:
    Menu(QWidget *parent, AppConfig *_config);

public slots:
    void removeDefaultXML();

private:
    AppConfig *config;
};


#endif //ROBOT_GUI_V3_MENU_H
