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
#define configSep ","
#define configNoXmlPath "none"


class Config {
public:
    static AppConfig *parseConfig();

    static void setConfig(AppConfig *config);

private:

    static bool createConfigDir();
    static void createConfigFile();
    static std::string getConfigPath();

    static bool fileExists(const std::string &name);

    static std::string split(const std::string &str, char delim, int index);
};


#endif //ROBOT_GUI_V3_CONFIG_H
