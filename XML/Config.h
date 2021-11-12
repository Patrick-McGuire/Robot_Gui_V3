//
// Created by patrick on 11/12/21.
//

#ifndef ROBOT_GUI_V3_CONFIG_H
#define ROBOT_GUI_V3_CONFIG_H
#include "iostream"
#include <unistd.h>
#include "experimental/filesystem"
#include <fstream>
#include <pwd.h>
#include "../ConfigStructs.h"

#define configFilePath "/.config/RobotGUI"
#define configFileName "/RobotGUI_Settings.csv"
#define configXmlPath "XML_PATH"
#define configSep ','
#define configNoXmlPath "none"

/* Notes:
 * Configuration data is stored in usr/<username>/home/.config/RobotGUI
 * This auto creates the RobotGUI folder when it runs the first time
 * Config data is stored in RobotGUI_Settings.csv in csv format
 */
class Config {
public:
    /**
     * This either creates or parses the configuration file for the app
     */
    void parseConfig();

    /**
     * This writes a AppConfig to the configuration file
     */
    void setConfig();

    void setDefaultXmlPath(std::string path);
    std::string getDefaultXmlPath();

private:
    std::string xmlFilepath;
    static bool createConfigDir();
    static void createConfigFile();
    static std::string getConfigPath();
    static bool fileExists(const std::string &name);
    static std::string split(const std::string &str, char delim, int index);
};
#endif //ROBOT_GUI_V3_CONFIG_H
