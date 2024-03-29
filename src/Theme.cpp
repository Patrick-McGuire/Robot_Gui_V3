#include "Theme.h"
#include "RobotGui.h"
#include "../lib/CommonFunctions.h"

RobotGui::Theme::Theme(RobotGui::Themes::Type type) {
    currentTheme = type;
    initFormats();
}

RobotGui::Theme::Theme(const std::string &type) {
    currentTheme = RobotGui::Themes::LIGHT;
    setTheme(type);
    initFormats();
}

std::string RobotGui::Theme::getBackgroundColor() {
    return stringFormats[currentTheme].backgroundColor;
}

std::string RobotGui::Theme::getWidgetBackgroundColor() {
    return stringFormats[currentTheme].widgetBackgroundColor;
}

std::string RobotGui::Theme::getTextColor() {
    return stringFormats[currentTheme].bodyTextColor;
}

std::string RobotGui::Theme::getHeaderColor() {
    return stringFormats[currentTheme].titleTextColor;
}

std::string RobotGui::Theme::getBorderColor() {
    return stringFormats[currentTheme].borderColor;
}

void RobotGui::Theme::setTheme(const std::string &name) {
    if (name == RobotGui::Themes::DARK_THEME_STR) {
        currentTheme = RobotGui::Themes::DARK;
    } else if (name == RobotGui::Themes::LIGHT_THEME_STR) {
        currentTheme = RobotGui::Themes::LIGHT;
    } else if (name == RobotGui::Themes::GREEN_THEME_STR) {
        currentTheme = RobotGui::Themes::GREEN;
    } else if(name == RobotGui::Themes::RED_THEME_STR) {
        currentTheme = RobotGui::Themes::RED;
    }
}

void RobotGui::Theme::setTheme(enum RobotGui::Themes::Type themeType) {
    currentTheme = themeType;
}

RobotGui::Themes::Type RobotGui::Theme::getTheme() {
    return currentTheme;
}

std::string RobotGui::Theme::getThemeName(RobotGui::Themes::Type themeType) {
    switch (themeType) {
        case RobotGui::Themes::DARK: {
            return RobotGui::Themes::DARK_THEME_STR;
        }
        case RobotGui::Themes::LIGHT: {
            return RobotGui::Themes::LIGHT_THEME_STR;
        }
        case RobotGui::Themes::GREEN: {
            return RobotGui::Themes::GREEN_THEME_STR;
        }
        case RobotGui::Themes::RED: {
            return RobotGui::Themes::RED_THEME_STR;
        }
    }
    return RobotGui::Themes::LIGHT_THEME_STR;
}

void RobotGui::Theme::initFormats() {
    // Initialize all themes
    stringFormats[RobotGui::Themes::DARK] = RobotGui::Themes::Format{
            "rgb(13,17,23)",
            "rgb(13, 17, 23)",
            "rgb(139,148,158)",
            "rgb(88,166,255)",
            "rgb(139,148,158)"
    };
    themeIsLight[RobotGui::Themes::DARK] = false;
    stringFormats[RobotGui::Themes::LIGHT] = RobotGui::Themes::Format{
            "rgb(250,250,250)",
            "rgb(250, 250, 250)",
            "rgb(0,0,0)",
            "rgb(0,0,0)",
            "rgb(0,0,0)"
    };
    themeIsLight[RobotGui::Themes::LIGHT] = true;
    stringFormats[RobotGui::Themes::GREEN] = RobotGui::Themes::Format{
            "rgb(20,20,20)",
            "rgb(25,25,25)",
            "rgb(150,150,150)",
            "rgb(10,200,10)",
            "rgb(50,50,50)"
    };
    themeIsLight[RobotGui::Themes::GREEN] = false;
    stringFormats[RobotGui::Themes::RED] = RobotGui::Themes::Format{
            "rgb(30,0,0)",
            "rgb(45,0,0)",
            "rgb(255,0,0)",
            "rgb(0,200,0)",
            "rgb(50,50,50)"
    };
    themeIsLight[RobotGui::Themes::RED] = false;
}

bool RobotGui::Theme::isLight() {
    return themeIsLight[currentTheme];
}

std::string RobotGui::Theme::getHighlightColor() {
    return CommonFunctions::GenerateDarkerColor(getBackgroundColor(), 20 * (isLight() ? 1 : -1));
}
