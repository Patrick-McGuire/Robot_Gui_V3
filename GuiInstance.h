#ifndef ROBOT_GUI_V3_GUIINSTANCE_H
#define ROBOT_GUI_V3_GUIINSTANCE_H
#include <QObject>
#include <QTimer>
#include "WidgetData.h"
#include "GUIMaker.h"
#include <QMainWindow>
#include "CustomWidgets/TabWidget.h"
#include "CustomWidgets/MenuWidget.h"
#include "CustomWidgets/SimpleButtonWidget.h"
#include "iostream"
#include <vector>
#include <QApplication>
#include "Interface/LocalServer.h"
#include "CoreGui.h"
#include "Theme.h"
#include "XML/XMLOutput.h"

class LocalServer;
class MenuWidget;
class CoreGui;

/**
 * @class GuiInstance
 * Runs the GUI
 *
 * @author Patrick McGuire (Patrick-McGuire)
 */
class GuiInstance : public QWidget {
Q_OBJECT
public:
    /**
     * Constructor
     * @param _parent QWidget to make parent
     * @param _mainWindow main window of the GUI
     * @param _appConfig global configuration data
     * @param _coreGui CoreGui object for connecting slots
     * @param _config window configuration data
     * @param _widgetData WidgetData object to display data from
     * @param _runState where to get data from
     */
    GuiInstance(QWidget *_parent, QMainWindow *_mainWindow, AppConfig *_appConfig, CoreGui *_coreGui, const RobotGui::WindowConfig_ptr& _config, WidgetData *_widgetData, RobotGui::GuiRunState _runState);

    /**
     * Deconstruct
     */
    ~GuiInstance();

    /**
     * Set the theme of the GUI
     * @param _theme theme to set
     * @param force whether or not to force the theme on all widgets
     */
    void setTheme();

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

    /**
     * Saves the curren config to XML
     */
    void save();

    /**
     * Saves the current config to XML
     */
     void saveAs();

private:
    /**
     * Resizes the main window
     */
    void setWindowSize();

    int timerUpdateTime;
    Theme *theme;
    QTimer *timer;
    RobotGui::GuiRunState runState;
    RobotGui::WindowConfig_ptr config;
    CoreGui *coreGui;
    WidgetData *widgetData;
    QMainWindow *mainWindow;
    MenuWidget *menu;
    BaseWidget *coreWidget;
    LocalServer *server;
    AppConfig *appConfig;
    QWidget *parent;
};


#endif //ROBOT_GUI_V3_GUIINSTANCE_H
