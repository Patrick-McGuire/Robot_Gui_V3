#ifndef ROBOT_GUI_V3_GUICORE_H
#define ROBOT_GUI_V3_GUICORE_H

#include <QWidget>
#include <QApplication>
#include <QWidget>
#include "iostream"
#include <QMainWindow>
#include "GuiInstance.h"
#include <vector>
#include "WidgetData.h"
#include <QDesktopWidget>
#include "RobotGui.h"
#include <QFileDialog>
#include "Config/AppConfig.h"
#include "thread"
#include "Interface/BaseInterface.h"
#include "Interface/ThreadedInterface.h"
#include "InternalJson.h"
#include "Interface/ServerInterface.h"

class GuiInstance;

class MenuWidget;

class ServerInterface;

namespace RobotGui {

    /**
     * @class CoreGui
     * Custom Manages the entire GUI
     *
     * @author Patrick McGuire (Patrick-McGuire)
     */
    class GuiCore : public QObject {
    Q_OBJECT
    public:
        BaseInterface *interface;

        /**
         * Constructor
         * @param argc
         * @param argv
         * @param _runState when to update the gui
         */
        GuiCore(int argc, char **argv);

        /**
         * Runs the gui
         * @return exit code
         */
        int runGUI();

        /**
         * Adds a thread for the GUI to close on exit
         * @param thread thread to close
         */
        void addInterface(ThreadedInterface *thread);

        /**
         * Adds a local server to the GUi
         * @param serverInterface serverInterface
         */
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

        std::vector<ThreadedInterface *> threads;
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

}

#endif //ROBOT_GUI_V3_GUICORE_H
