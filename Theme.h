#ifndef ROBOT_GUI_V3_THEME_H
#define ROBOT_GUI_V3_THEME_H

#include "string"
#include "map"
#include "RobotGui.h"

class Theme {
public:
    /**
     * Constructor
     * @param type Theme type
     */
    explicit Theme(RobotGui::Themes::Type type);

    /**
     * Constructor
     * @param type Theme type
     */
    explicit Theme(const std::string &type);

    /**
     * Returns a string containing the background color for the current theme
     * @return background color string
     */
    std::string getBackgroundColor();

    /**
     * Returns a string containing the widget background color for the current theme
     * @return widget background color string
     */
    std::string getWidgetBackgroundColor();

    /**
     * Returns a string containing the text color for the current theme
     * @return text color string
     */
    std::string getTextColor();

    /**
     * Returns a string containing the header text color for the current theme
     * @return header text color string
     */
    std::string getHeaderTextColor();

    /**
     * Returns a string containing the border color for the current theme
     * @return border color string
     */
    std::string getBorderColor();

    /**
     * Returns a string containing the highlight color for the current theme
     * @return highlight color string
     */
    std::string getHighlightColor();

    /**
     * Sets the current theme
     * @param name name of theme to set
     */
    void setTheme(const std::string &name);

    /**
     * Sets the current theme
     * @param themeType theme to set
     */
    void setTheme(enum RobotGui::Themes::Type themeType);

    /**
     * Returns the current theme
     * @return current theme
     */
    RobotGui::Themes::Type getTheme();

    /**
     * Returns if the current theme is a "light" theme
     * @return if light
     */
    bool isLight();

    /**
     * Gets name of a theme enum
     * @param themeType Theme to get name of
     * @return Name of the theme
     */
    static std::string getThemeName(RobotGui::Themes::Type themeType);

private:
    /**
     * Initializes the format maps with theme format colors
     */
    void initFormats();

    RobotGui::Themes::Type currentTheme;
    std::map<RobotGui::Themes::Type, RobotGui::Themes::Format> stringFormats;
    std::map<RobotGui::Themes::Type, bool> themeIsLight;
};


#endif //ROBOT_GUI_V3_THEME_H
