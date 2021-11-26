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

/**
 * @class TextBoxWidget
 * Custom QWidget that creates tabs with children widgets
 * This is not a configurable widget like most custom widgets, this is hardcoded and created for every GUI
 *
 * @author Patrick McGuire (Patrick-McGuire)
 */
class MenuWidget : public QMenuBar {
Q_OBJECT
public:
    /**
     * Constructor
     * @param parent QWidget to make parent, should be a MainWindow
     * @param appConfig_ configuration data
     * @param coreGui CoreGUI class for connecting slot
     * @param robotGui RobotGUI class for connecting slot
     */
    MenuWidget(QWidget *parent, AppConfig *appConfig_, CoreGUI *coreGui, RobotGUI *robotGui);

    /**
     * Updates the menu bar's theme
     * @param _theme theme to set
     */
    void updateTheme(Themes _theme);

private:
    AppConfig *appConfig;
    std::vector<QMenu*> menus;
};


#endif //ROBOT_GUI_V3_MENUWIDGET_H
