//
// Created by patrick on 11/16/21.
//

#ifndef ROBOT_GUI_V3_THEME_H
#define ROBOT_GUI_V3_THEME_H
#include "string"

//# Theme colors are defined as Background, WidgetBackground, Default Text, Header Text, Border
//self.themes["Better Dark"] = ["rgb[13, 17, 23]", "rgb[13, 17, 23]", "rgb[139,148,158]", "rgb[88,166,255]", "rgb[139,148,158]"]
#define darkThemeBackgroundColor "rgb(13,17,23)"
#define darkThemeWidgetBackgroundColor "rgb(13, 17, 23)"
#define darkThemeTextColor "rgb(139,148,158)"
#define darkThemeHeaderTextColor "rgb(88,166,255)"
#define darkThemeBorderColor "rgb(139,148,158)"

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
    static std::string getHeaderTextColor(Themes theme);
    static std::string getThemeBorderColor(Themes theme);
};


#endif //ROBOT_GUI_V3_THEME_H
