//
// Created by patrick on 11/16/21.
//

#include "Theme.h"

std::string Theme::getBackgroundColorStr(Themes theme) {
    switch (theme) {
        case Dark: {
            return darkThemeBackgroundColor;
            break;
        }
        case Light: {
            break;
        } case Green: {
            break;
        } case QtDefault: {
            break;
        }
    }
    return "rgb(255,255,255)";
}

std::string Theme::getWidgetBackgroundColorStr(Themes theme) {
    return darkThemeWidgetBackgroundColor;
}

std::string Theme::getTextColorStr(Themes theme) {
    return darkThemeTextColor;
}

std::string Theme::getHeaderTextColor(Themes theme) {
    return darkThemeHeaderTextColor;
}

std::string Theme::getThemeBorderColor(Themes theme) {
    return darkThemeBorderColor;
}
