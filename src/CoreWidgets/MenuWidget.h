#ifndef ROBOT_GUI_V3_MENUWIDGET_H
#define ROBOT_GUI_V3_MENUWIDGET_H

#include "../CustomWidgets/BaseWidget.h"
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
#include "../GuiCore.h"
#include "../Theme.h"
#include "../GuiInstance.h"
#include "../Theme.h"

namespace RobotGui {
    class GuiCore;

    class GuiInstance;

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
        MenuWidget(QWidget *parent, AppConfig *appConfig_, GuiCore *coreGui, GuiInstance *robotGui, Theme *_theme);

        /**
         * Updates the menu bar's theme
         * @param _theme theme to set
         */
        void updateTheme();

    private:
        Theme *theme;
        AppConfig *appConfig;
        std::vector<QMenu *> menus;
        const char *const FILE_MENU_NAME = "FileMenu";
        const char *const SETTINGS_MENU_NAME = "SettingMenuName";
        const char *const THEME_MENU_NAME = "ThemeMenu";
    };
}


#endif //ROBOT_GUI_V3_MENUWIDGET_H
