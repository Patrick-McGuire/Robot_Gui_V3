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

std::string Theme::getHeaderTextColorStr(Themes theme) {
    return darkThemeHeaderTextColor;
}

std::string Theme::getBorderColorStr(Themes theme) {
    return darkThemeBorderColor;
}

std::string Theme::getRightClickMenuBackgroundColorStr(Themes theme) {
    return darkThemeRightClickMenuBackgroundColor;
}

std::string Theme::getRightClickMenuHighlightColorStr(Themes themes) {
    return darkThemeRightClickMenuHighlightColor;
}
