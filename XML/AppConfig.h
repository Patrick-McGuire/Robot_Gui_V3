#ifndef ROBOT_GUI_V3_APPCONFIG_H
#define ROBOT_GUI_V3_APPCONFIG_H
#include "iostream"
#include <unistd.h>
#include "experimental/filesystem"
#include <fstream>
#include <pwd.h>
#include "../RobotGui.h"

/* Notes:
 * Configuration data is stored in usr/<username>/home/.config/GuiInstance
 * This auto creates the GuiInstance folder + config file when it runs the first time
 * AppConfig data is stored in RobotGUI_Settings.csv in csv format
 */
/**
 * @class AppConfig
 * Stores global configuration data in .config for the app
 *
 * @author Patrick McGuire (Patrick-McGuire)
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
     * @param path[in] path to save
     */
    void setDefaultXmlPath(std::string path);

    /**
     * Gets the path to the xml config file, parse() needs to be called first
     * @return path to the xml file
     */
    std::string getDefaultXmlPath() const;

    /**
     * Checks if a file exists
     * @param path[in] path + filename to check
     * @return if file exists
     */
    static bool fileExists(const std::string &path);

private:
    std::string xmlFilepath;

    /**
     * Trys to create the directory ~/.config/GuiInstance
     * @return true if created, false if already exists
     */
    static bool createDir();

    /**
     * Creates the config file in ~/.config/GuiInstance
     */
    static void createFile();

    /**
     * Gets the path to .config for current user
     * @return path to .config for current user
     */
    static std::string getPath();

    /**
     * Returns a segment of a string based on a delimiter and index
     * @param str[in] string to splitStr
     * @param delim[in] separator
     * @param index [in] index
     * @return segment of string
     */
    static std::string splitStr(const std::string &str, char delim, int index);
};
#endif //ROBOT_GUI_V3_APPCONFIG_H
