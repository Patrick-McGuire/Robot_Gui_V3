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
            return lightThemeBackgroundColor;
            break;
        } case Green: {
            return greenThemeBackgroundColor;
            break;
        } case QtDefault: {
            break;
        }
    }
    return "rgb(255,255,255)";
}

std::string Theme::getWidgetBackgroundColorStr(Themes theme) {
    switch (theme) {
        case Dark: {
            return darkThemeWidgetBackgroundColor;
            break;
        }
        case Light: {
            return lightThemeWidgetBackgroundColor;
            break;
        }
        case Green: {
            return greenThemeWidgetBackgroundColor;
            break;
        }
        case QtDefault: {

            break;
        }
    }
    return "rgb(255,255,255)";
}

std::string Theme::getTextColorStr(Themes theme) {
    switch (theme) {
        case Dark: {
            return darkThemeTextColor;
            break;
        }
        case Light: {
            return lightThemeTextColor;
            break;
        }
        case Green: {
            return greenThemeTextColor;
            break;
        }
        case QtDefault: {

            break;
        }
    }
    return "rgb(0,0,0)";
}

std::string Theme::getHeaderTextColorStr(Themes theme) {
    switch (theme) {
        case Dark: {
            return darkThemeHeaderTextColor;
            break;
        }
        case Light: {
            return lightThemeHeaderTextColor;
            break;
        }
        case Green: {
            return greenThemeHeaderTextColor;
            break;
        }
        case QtDefault: {

            break;
        }
    }
    return "rgb(0,0,0)";
}

std::string Theme::getBorderColorStr(Themes theme) {
    switch (theme) {
        case Dark: {
            return darkThemeBorderColor;
            break;
        }
        case Light: {
            return lightThemeBorderColor;
            break;
        }
        case Green: {
            return greenThemeBorderColor;
            break;
        }
        case QtDefault: {

            break;
        }
    }
    return "rgb(255,255,255)";
}

std::string Theme::getRightClickMenuBackgroundColorStr(Themes theme) {
    switch (theme) {
        case Dark: {
            return darkThemeRightClickMenuBackgroundColor;
            break;
        }
        case Light: {
            return lightThemeRightClickMenuBackgroundColor;
            break;
        }
        case Green: {
            return greenThemeRightClickMenuBackgroundColor;
            break;
        }
        case QtDefault: {

            break;
        }
    }
    return "rgb(255,255,255)";
}

std::string Theme::getRightClickMenuHighlightColorStr(Themes theme) {
    switch (theme) {
        case Dark: {
            return darkThemeRightClickMenuHighlightColor;
            break;
        }
        case Light: {
            return lightThemeRightClickMenuHighlightColor;
            break;
        }
        case Green: {
            return greenThemeRightClickMenuHighlightColor;
            break;
        }
        case QtDefault: {

            break;
        }
    }
    return "rgb(255,255,255)";
}

std::string Theme::getThemeName(Themes theme) {
    switch (theme) {
        case Dark: {
            return darkThemeStr;
            break;
        }
        case Light: {
            return lightThemeStr;
            break;
        }
        case Green: {
            return greenThemeStr;
            break;
        }
        case QtDefault: {
            return qtDefaultThemeStr;
        }
    }
    return qtDefaultThemeStr;
}

Themes Theme::getThemeFromName(const std::string& name) {
    Themes out = QtDefault;
    if(name == darkThemeStr) {
        out = Dark;
    } else if(name == lightThemeStr) {
        out = Light;
    } else if(name == greenThemeStr) {
        out = Green;
    } else if(name == qtDefaultThemeStr) {
        out = QtDefault;
    }
    return out;
}
