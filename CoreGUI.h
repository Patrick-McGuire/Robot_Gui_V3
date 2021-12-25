#ifndef ROBOT_GUI_V3_COREGUI_H
#define ROBOT_GUI_V3_COREGUI_H

#include <QWidget>
#include <QApplication>
#include <QWidget>
#include "iostream"
#include <QMainWindow>
#include "RobotGUI.h"
#include <vector>
#include "WidgetData.h"
#include "Networking/LocalServer.h"
#include <QDesktopWidget>
#include "Constants.h"
#include <QFileDialog>
#include "XML/AppConfig.h"
#include "thread"
#include "Interface/BaseInterface.h"

class RobotGUI;
class MenuWidget;

/**
 * @class CoreGUI
 * Custom Manages the entire GUI
 *
 * @author Patrick McGuire (Patrick-McGuire)
 */
class CoreGUI : public QObject{
Q_OBJECT
public:
    BaseInterface *interface;

    /**
     * Constructor
     * @param argc
     * @param argv
     */
    CoreGUI(int argc, char** argv);

    /**
     * Runs the gui
     * @return exit code
     */
    int runGUI();

    /**
     * Returns widgetData
     * @return widgetData
     */
    WidgetData *getWidgetData();

    void test(WidgetData *widgetData);

public slots:
    /**
     * Reloads the GUI with the current configuration
     */
    void reload();

    /**
     * Reprises the xml file and reloads the GUI
     */
    void reparseReload();

    /**
     * Opens a new GUI configuration
     */
    void openReload();

private:
    bool quit = false;
    int argc;
    char **argv;
    WindowConfig_ptr windowConfig;
    AppConfig *appConfig;
    QApplication app;
    QMainWindow mainWindow;
    QWidget window;
    QWidget *wrapper;
    RobotGUI *currentRobotGUI;
    WidgetData *widgetData;

    /**
     * Restarts the RobotGUI instance
     */
    void restartGUI();

    /**
     * Parses xml, and catches errors
     * @return if successful
     */
    bool safeParse();

    /**
     * Gets a file path
     * @return file path
     */
    std::string getFilePath();
};


#endif //ROBOT_GUI_V3_COREGUI_H
