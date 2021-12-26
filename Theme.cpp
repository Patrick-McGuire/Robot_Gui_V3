#include "Theme.h"

Theme::Theme(RobotGui::Themes::Type type) {
    currentTheme = type;
    initFormats();
}

Theme::Theme(const std::string& type) {
    currentTheme = RobotGui::Themes::LIGHT;
    setTheme(type);
    initFormats();
}

std::string Theme::getBackgroundColorStr() {
    return stringFormats[currentTheme].backgroundColor;
}

std::string Theme::getWidgetBackgroundColorStr() {
    return stringFormats[currentTheme].widgetBackgroundColor;
}

std::string Theme::getTextColorStr() {
    return stringFormats[currentTheme].bodyTextColor;
}

std::string Theme::getHeaderTextColorStr() {
    return stringFormats[currentTheme].titleTextColor;
}

std::string Theme::getBorderColorStr() {
    return stringFormats[currentTheme].borderColor;
}

void Theme::setTheme(const std::string &name) {
    if(name == RobotGui::Themes::DARK_THEME_STR) {
        currentTheme = RobotGui::Themes::DARK;
    } else if(name == RobotGui::Themes::LIGHT_THEME_STR) {
        currentTheme = RobotGui::Themes::LIGHT;
    } else if(name == RobotGui::Themes::GREEN_THEME_STR) {
        currentTheme = RobotGui::Themes::GREEN;
    }
}

void Theme::setTheme(enum RobotGui::Themes::Type themeType) {
    currentTheme = themeType;
}

RobotGui::Themes::Type Theme::getTheme() {
    return currentTheme;
}

std::string Theme::getThemeName(RobotGui::Themes::Type themeType) {
    switch (themeType) {
        case RobotGui::Themes::DARK: {
            return RobotGui::Themes::DARK_THEME_STR;
            break;
        }
        case RobotGui::Themes::LIGHT: {
            return RobotGui::Themes::LIGHT_THEME_STR;
            break;
        }
        case RobotGui::Themes::GREEN: {
            return RobotGui::Themes::GREEN_THEME_STR;
            break;
        }
    }
    return RobotGui::Themes::LIGHT_THEME_STR;
}

void Theme::initFormats() {
    // Initialize all themes
    stringFormats[RobotGui::Themes::DARK] = RobotGui::Themes::Format {
            "rgb(13,17,23)",
            "rgb(13, 17, 23)",
            "rgb(139,148,158)",
            "rgb(88,166,255)",
            "rgb(139,148,158)"
    };
    stringFormats[RobotGui::Themes::LIGHT] = RobotGui::Themes::Format {
            "rgb(250,250,250)",
            "rgb(250, 250, 250)",
            "rgb(0,0,0)",
            "rgb(0,0,0)",
            "rgb(0,0,0)"
    };
    stringFormats[RobotGui::Themes::GREEN] = RobotGui::Themes::Format {
            "rgb(20,20,20)",
            "rgb(25,25,25)",
            "rgb(150,150,150)",
            "rgb(10,200,10)",
            "rgb(50,50,50)"
    };
}
