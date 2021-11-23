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
//        self.themes["Green Text"] = ["rgb[20, 20, 20]", "rgb[25, 25, 25]", "rgb[150,150,150]", "rgb[10,200,10]", "rgb[50,50,50]"]
// Green theme
#define greenThemeBackgroundColor "rgb(20,20,20)"
#define greenThemeWidgetBackgroundColor "rgb(25, 25, 25)"
#define greenThemeTextColor "rgb(150,150,150)"
#define greenThemeHeaderTextColor "rgb(10,200,10)"
#define greenThemeBorderColor "rgb(50,50,50)"
#define greenThemeRightClickMenuBackgroundColor "rgb(40,40,40)"
#define greenThemeRightClickMenuHighlightColor "rgb(60,60,60)"

enum Themes {
    Dark=0,
    Light=1,
    Green=2,
    QtDefault=3,
};


class Theme {
public:
    static std::string getBackgroundColorStr(Themes theme);
    static std::string getWidgetBackgroundColorStr(Themes theme);
    static std::string getTextColorStr(Themes theme);
    static std::string getHeaderTextColorStr(Themes theme);
    static std::string getBorderColorStr(Themes theme);
    static std::string getRightClickMenuBackgroundColorStr(Themes theme);
    static std::string getRightClickMenuHighlightColorStr(Themes theme);
    static std::string getThemeName(Themes theme);
    static Themes getThemeFromName(const std::string& name);
};


#endif //ROBOT_GUI_V3_THEME_H
