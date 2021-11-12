//
// Created by patrick on 11/12/21.
//

#ifndef ROBOT_GUI_V3_APPCONFIG_H
#define ROBOT_GUI_V3_APPCONFIG_H
#include "iostream"
#include <unistd.h>
#include "experimental/filesystem"
#include <fstream>
#include <pwd.h>
#include "../ConfigStructs.h"
#include "../Constants.h"

/* Notes:
 * Configuration data is stored in usr/<username>/home/.config/RobotGUI
 * This auto creates the RobotGUI folder when it runs the first time
 * AppConfig data is stored in RobotGUI_Settings.csv in csv format
 */
class AppConfig {
public:
    /**
     * This either creates or parses the configuration file for the app
     */
    void parse();

    /**
     * This writes a AppConfig to the configuration file
     */
    void write();

    /**
     * Sets the path to the xml config file, but does not save it
     * @param path path to save
     */
    void setDefaultXmlPath(std::string path);

    /**
     * Gets the path to the xml config file, parse() needs to be called first
     * @return path to the xml file
     */
    std::string getDefaultXmlPath();

private:
    std::string xmlFilepath;
    static bool createDir();
    static void createFile();
    static std::string getPath();
    static bool fileExists(const std::string &name);
    static std::string split(const std::string &str, char delim, int index);
};
#endif //ROBOT_GUI_V3_APPCONFIG_H
