#ifndef ROBOT_GUI_V3_MENUWIDGET_H
#define ROBOT_GUI_V3_MENUWIDGET_H

#include "BaseWidget.h"
#include <QWidget>
#include <QLabel>
#include <string>
#include <QGridLayout>
#include <string>
#include "../WidgetData.h"
#include "../RobotGui.h"
#include <string>
#include "QWidget"
#include "QMouseEvent"
#include "QMenuBar"
#include "iostream"
#include "../GuiInstance.h"
#include "../CoreGui.h"
#include "../Theme.h"

class GuiInstance;
class CoreGui;

#define FILE_MENU_NAME "FileMenu"
#define SETTINGS_MENU_NAME "SettingMenuName"
#define THEME_MENU_NAME "ThemeMenu"

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
     * @param coreGui CoreGui class for connecting slot
     * @param robotGui GuiInstance class for connecting slot
     */
    MenuWidget(QWidget *parent, AppConfig *appConfig_, CoreGui *coreGui, GuiInstance *robotGui, Theme *_theme);

    /**
     * Updates the menu bar's theme
     * @param _theme theme to set
     */
    void updateTheme();

private:
    Theme *theme;
    AppConfig *appConfig;
    std::vector<QMenu*> menus;
};


#endif //ROBOT_GUI_V3_MENUWIDGET_H
