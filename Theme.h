#ifndef ROBOT_GUI_V3_THEME_H
#define ROBOT_GUI_V3_THEME_H

#include "string"
#include "map"
#include "RobotGui.h"


class Theme {
public:
    explicit Theme(RobotGui::Themes::Type type);
    explicit Theme(const std::string& type);

    std::string getBackgroundColorStr();
    std::string getWidgetBackgroundColorStr();
    std::string getTextColorStr();
    std::string getHeaderTextColorStr();
    std::string getBorderColorStr();

    void setTheme(const std::string& name);
    void setTheme(enum RobotGui::Themes::Type themeType);
    RobotGui::Themes::Type getTheme();

    static std::string getThemeName(RobotGui::Themes::Type themeType);
private:
    void initFormats();

    RobotGui::Themes::Type currentTheme;
    std::map<RobotGui::Themes::Type, RobotGui::Themes::Format> stringFormats;
};


#endif //ROBOT_GUI_V3_THEME_H
