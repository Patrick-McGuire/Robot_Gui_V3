//
// Created by patrick on 11/15/21.
//

#ifndef ROBOT_GUI_V3_MENUWIDGET_H
#define ROBOT_GUI_V3_MENUWIDGET_H

#include "BaseWidget.h"
#include <QWidget>
#include <QLabel>
#include <string>
#include <QGridLayout>
#include "../ConfigStructs.h"
#include <string>
#include "../WidgetData.h"
#include "../Constants.h"
#include "../XML/XMLConstants.h"
#include <string>
#include "QWidget"
#include "QMouseEvent"
#include "QMenuBar"
#include "iostream"
#include "../RobotGUI.h"
#include "../CoreGUI.h"
#include "../Theme.h"

class RobotGUI;
class CoreGUI;

#define fileMenuName "FileMenu"
#define settingsMenuName "SettingMenuName"
#define themeMenuName "ThemeMenu"

///// This is not a configurable widget like most custom widgets, this is hardcoded and created for every GUI
class MenuWidget : public QMenuBar {
Q_OBJECT
public:
    MenuWidget(QWidget *parent, AppConfig *appConfig_, CoreGUI *coreGui, RobotGUI *robotGui);
    void updateTheme(Themes _theme);

private:
    AppConfig *appConfig;
    std::vector<QMenu*> menus;
};


#endif //ROBOT_GUI_V3_MENUWIDGET_H
