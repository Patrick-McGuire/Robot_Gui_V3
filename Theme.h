//
// Created by patrick on 11/16/21.
//

#ifndef ROBOT_GUI_V3_THEME_H
#define ROBOT_GUI_V3_THEME_H
#include "string"

#define darkThemeStr "Dark"
#define lightThemeStr "Light"
#define greenThemeStr "Green"
#define qtDefaultThemeStr "QtDefault"

//# Theme colors are defined as Background, WidgetBackground, Default Text, Header Text, Border
// Dark theme
#define darkThemeBackgroundColor "rgb(13,17,23)"
#define darkThemeWidgetBackgroundColor "rgb(13, 17, 23)"
#define darkThemeTextColor "rgb(139,148,158)"
#define darkThemeHeaderTextColor "rgb(88,166,255)"
#define darkThemeBorderColor "rgb(139,148,158)"
#define darkThemeRightClickMenuBackgroundColor "rgb(40,40,40)"
#define darkThemeRightClickMenuHighlightColor "rgb(60,60,60)"
// Green theme
#define greenThemeBackgroundColor "rgb(20,20,20)"
#define greenThemeWidgetBackgroundColor "rgb(25,25,25)"
#define greenThemeTextColor "rgb(150,150,150)"
#define greenThemeHeaderTextColor "rgb(10,200,10)"
#define greenThemeBorderColor "rgb(50,50,50)"
#define greenThemeRightClickMenuBackgroundColor "rgb(40,40,40)"
#define greenThemeRightClickMenuHighlightColor "rgb(60,60,60)"
// Light theme
#define lightThemeBackgroundColor "rgb(250,250,250)"
#define lightThemeWidgetBackgroundColor "rgb(250, 250, 250)"
#define lightThemeTextColor "rgb(0,0,0)"
#define lightThemeHeaderTextColor "rgb(0,0,0)"
#define lightThemeBorderColor "rgb(0,0,0)"
#define lightThemeRightClickMenuBackgroundColor "rgb(250,250,250)"
#define lightThemeRightClickMenuHighlightColor "rgb(200,200,200)"

enum Themes {
    Dark=0,
    Light=1,
    Green=2,
    QtDefault=3,
};


/**
 * @class Theme
 * Handles theme constants
 *
 * @author Patrick McGuire (Patrick-McGuire)
 */
class Theme {
public:

    /**
     * Gets the background color rgb string for a given theme
     * @param theme given theme
     * @return qStylesheet compatible rgb string
     */
    static std::string getBackgroundColorStr(Themes theme);

    /**
     * Gets the widget background color rgb string for a given theme
     * @param theme given theme
     * @return qStylesheet compatible rgb string
     */
    static std::string getWidgetBackgroundColorStr(Themes theme);

    /**
     * Gets the text color rgb string for a given theme
     * @param theme given theme
     * @return qStylesheet compatible rgb string
     */
    static std::string getTextColorStr(Themes theme);

    /**
     * Gets the header text color rgb string for a given theme
     * @param theme given theme
     * @return qStylesheet compatible rgb string
     */
    static std::string getHeaderTextColorStr(Themes theme);

    /**
     * Gets the border color rgb string for a given theme
     * @param theme given theme
     * @return qStylesheet compatible rgb string
     */
    static std::string getBorderColorStr(Themes theme);

    /**
     * Gets the right click menu background color rgb string for a given theme
     * @param theme given theme
     * @return qStylesheet compatible rgb string
     */
    static std::string getRightClickMenuBackgroundColorStr(Themes theme);

    /**
     * Gets the right click menu background highlight color rgb string for a given theme
     * @param theme given theme
     * @return qStylesheet compatible rgb string
     */
    static std::string getRightClickMenuHighlightColorStr(Themes theme);

    /**
     * Gets name of a given theme
     * @param theme given theme
     * @return name of theme
     */
    static std::string getThemeName(Themes theme);

    /**
     * Gets theme enum for a given theme name
     * @param theme given theme name
     * @return theme enum
     */
    static Themes getThemeFromName(const std::string& name);
};


#endif //ROBOT_GUI_V3_THEME_H
