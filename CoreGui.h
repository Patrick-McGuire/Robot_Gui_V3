#ifndef ROBOT_GUI_V3_COREGUI_H
#define ROBOT_GUI_V3_COREGUI_H

#include <QWidget>
#include <QApplication>
#include <QWidget>
#include "iostream"
#include <QMainWindow>
#include "GuiInstance.h"
#include <vector>
#include "WidgetData.h"
#include "Interface/LocalServer.h"
#include <QDesktopWidget>
#include "RobotGui.h"
#include <QFileDialog>
#include "XML/AppConfig.h"
#include "thread"
#include "Interface/BaseInterface.h"
#include "Interface/ThreadedInterface.h"
#include "InternalJson.h"
#include "Interface/ServerInterface.h"

class GuiInstance;
class MenuWidget;
class ServerInterface;

/**
 * @class CoreGui
 * Custom Manages the entire GUI
 *
 * @author Patrick McGuire (Patrick-McGuire)
 */
class CoreGui : public QObject{
Q_OBJECT
public:
    BaseInterface *interface;

    /**
     * Constructor
     * @param argc
     * @param argv
     * @param _runState when to update the gui
     */
    CoreGui(int argc, char** argv, RobotGui::GuiRunState _runState);

    /**
     * Runs the gui
     * @return exit code
     */
    int runGUI();

    /**
     * Adds a thread for the GUI to close on exit
     * @param thread thread to close
     */
    void addThreadedInterface(ThreadedInterface *thread);

    void addInterface(ServerInterface *serverInterface);

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
    /**
     * Restarts the GuiInstance instance
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

    RobotGui::GuiRunState runState;
    std::vector<ThreadedInterface*> threads;
    bool quit = false;
    RobotGui::WindowConfig_ptr windowConfig;
    AppConfig *appConfig;
    QApplication app;
    QMainWindow mainWindow;
    QWidget window;
    QWidget *wrapper;
    GuiInstance *currentRobotGUI;
    WidgetData *widgetData;
};


#endif //ROBOT_GUI_V3_COREGUI_H
