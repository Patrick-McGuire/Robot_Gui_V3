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
    }
    return "rgb(255,255,255)";
}

std::string Theme::getThemeName(Themes theme) {
    switch (theme) {
        case Dark: {
            return DARK_THEME_STR;
            break;
        }
        case Light: {
            return LIGHT_THEME_STR;
            break;
        }
        case Green: {
            return GREEN_THEME_STR;
            break;
        }
    }
    return LIGHT_THEME_STR;
}

Themes Theme::getThemeFromName(const std::string& name) {
    Themes out = Light;
    if(name == DARK_THEME_STR) {
        out = Dark;
    } else if(name == LIGHT_THEME_STR) {
        out = Light;
    } else if(name == GREEN_THEME_STR) {
        out = Green;
    }
    return out;
}
