#ifndef ROBOT_GUI_V3_ROBOTGUI_H
#define ROBOT_GUI_V3_ROBOTGUI_H
#include <QObject>
#include <QTimer>
#include "WidgetData.h"
#include "GUIMaker.h"
#include <QMainWindow>
#include "CustomWidgets/TabWidget.h"
#include "ConfigStructs.h"
#include "CustomWidgets/MenuWidget.h"
#include "CustomWidgets/SimpleButtonWidget.h"
#include "iostream"
#include <vector>
#include <QApplication>
#include "Networking/LocalServer.h"
#include "CoreGUI.h"
#include "Theme.h"

class LocalServer;
class MenuWidget;
class CoreGUI;

/**
 * @class RobotGUI
 * Runs the GUI
 *
 * @author Patrick McGuire (Patrick-McGuire)
 */
class RobotGUI : public QWidget {
Q_OBJECT
public:
    /**
     * Constructor
     * @param _parent QWidget to make parent
     * @param _mainWindow main window of the GUI
     * @param _appConfig global configuration data
     * @param _coreGui CoreGUI object for connecting slots
     * @param _config window configuration data
     */
    RobotGUI(QWidget *_parent, QMainWindow *_mainWindow, AppConfig *_appConfig, CoreGUI *_coreGui, const WindowConfig_ptr& _config, WidgetData *_widgetData, GuiRunState _runState);

    /**
     * Deconstruct
     */
    ~RobotGUI();

    /**
     * Set the theme of the GUI
     * @param _theme theme to set
     * @param force whether or not to force the theme on all widgets
     */
    void setTheme(Themes _theme, bool force);

    /**
     * Returns widgetData
     * @return widgetData
     */
    WidgetData *getWidgetData();

public slots:
    /**
     * Slot that updates the every child custom widget
     */
    void updateGUI();

    /**
     * Makes all children custom widgets draggable
     */
    void makeWidgetsDraggable();

    /**
     * Makes all children custom widgets fixed
     */
    void makeWidgetsFixed();

    /**
     * Sets the theme for the gui
     * @param channelAction object contain theme to set
     */
    void updateTheme(QAction *channelAction);

    /**
     * Forces the theme on to all widgets
     * @param channelAction object contain theme to set
     */
    void forceTheme(QAction *channelAction);

private:
    /**
     * Resizes the main window
     */
    void setWindowSize();

    int timerUpdateTime = 10;
    QTimer *timer;
    GuiRunState runState;
    WindowConfig_ptr config;
    CoreGUI *coreGui;
    WidgetData *widgetData;
    QMainWindow *mainWindow;
    MenuWidget *menu;
    BaseWidget *coreWidget;
    LocalServer *server;
    AppConfig *appConfig;
    QWidget *parent;
};


#endif //ROBOT_GUI_V3_ROBOTGUI_H
