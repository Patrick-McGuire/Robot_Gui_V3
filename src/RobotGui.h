#ifndef ROBOT_GUI_V3_ROBOTGUI_H
#define ROBOT_GUI_V3_ROBOTGUI_H

#include <string>
#include <vector>
#include <map>
#include "Config/AppConfig.h"
#include "array"
#include "CustomWidgets/BaseStructure/WidgetBaseConfig.h"


namespace RobotGui {
    //// Enums ////
    // TCP server data input types
    enum MessageType {
        JSON = 3,
        IMG = 4,
    };
    // TCP server data output types
    enum ReturnType {
        NO_RETURN = 0,
        RETURN_FLAGS = 1,
        RETURN_VALUES = 2,
        RETURN_FLAGS_AND_VALUES = 3,
    };

    namespace WidgetConstants {
        enum Requirements {
            TITLE,
            SOURCE,
            HEIGHT,
            WIDTH,
            SIZE,
            MIN,
            MAX,
            RANGE,
            ROW_NUMBER,
            COLUMN_NUMBER,
            FONT,
            BACKGROUND_COLOR,
            FOREGROUND_COLOR,
            RELIEF,
            TEXT_COLOR,
            HEADER_COLOR,
            BORDER_COLOR,
            FONT_Size,
            BORDER_Width,
        };
        enum Type : int {
            NO_TYPE,
            TEXT_BOX,
            VIDEO,
            TAB,
            SIMPLE_BUTTON,
            MULTI_BAR_GRAPH,
            ANNUNCIATOR_PANEL,
            SIMPLE_CONSOLE,
            ROV_STATUS,
            COMPLETE_CONSOLE,
            MISSION_STATUS,
            DROP_DOWN_TEXT_BOX,
            COMPASS,
            LIVE_PLOT,
            SETTINGS_TAB,
            ATTITUDE_DISPLAY,
        };
        // Widget types
        const char *const TEXT_BOX_STRID = "textBox";
        const char *const VIDEO_STRID = "video";
        const char *const TAB_STRID = "tab";
        const char *const SIMPLE_BUTTON_STRID = "simpleButton";
        const char *const MULTI_BAR_GRAPH_STRID = "multiBarGraph";
        const char *const ANNUNCIATOR_PANEL_STRID = "annunciatorPanel";
        const char *const SIMPLE_CONSOLE_STRID = "simpleConsole";
        const char *const ROV_STATUS_STRID = "ROVStatusWidget";
        const char *const COMPLETE_CONSOLE_STRID = "completeConsole";
        const char *const MISSION_STATUS_STRID = "missionStatusWidget";
        const char *const DROP_DOWN_TEXT_BOX_STRID = "dropDownTextBox";
        const char *const COMPASS_STRID = "compass";
        const char *const LIVE_PLOT_STRID = "livePlot";
        const char *const SETTINGS_TAB_STRID = "settingsTab";
        const char *const ATTITUDE_DISPLAY_STRID = "attitudeWidget";

        inline Type getWidgetType(const std::string &_type) {
            WidgetConstants::Type type1 = RobotGui::WidgetConstants::NO_TYPE;
            if (_type == WidgetConstants::TEXT_BOX_STRID) {
                type1 = RobotGui::WidgetConstants::TEXT_BOX;
            } else if (_type == WidgetConstants::VIDEO_STRID) {
                type1 = RobotGui::WidgetConstants::VIDEO;
            } else if (_type == WidgetConstants::TAB_STRID) {
                type1 = RobotGui::WidgetConstants::TAB;
            } else if (_type == WidgetConstants::SIMPLE_BUTTON_STRID) {
                type1 = RobotGui::WidgetConstants::SIMPLE_BUTTON;
            } else if (_type == WidgetConstants::MULTI_BAR_GRAPH_STRID) {
                type1 = RobotGui::WidgetConstants::MULTI_BAR_GRAPH;
            } else if (_type == WidgetConstants::ANNUNCIATOR_PANEL_STRID) {
                type1 = RobotGui::WidgetConstants::ANNUNCIATOR_PANEL;
            } else if (_type == WidgetConstants::SIMPLE_CONSOLE_STRID) {
                type1 = RobotGui::WidgetConstants::SIMPLE_CONSOLE;
            } else if (_type == WidgetConstants::ROV_STATUS_STRID) {
                type1 = RobotGui::WidgetConstants::ROV_STATUS;
            } else if (_type == WidgetConstants::COMPLETE_CONSOLE_STRID) {
                type1 = RobotGui::WidgetConstants::COMPLETE_CONSOLE;
            } else if (_type == WidgetConstants::MISSION_STATUS_STRID) {
                type1 = RobotGui::WidgetConstants::MISSION_STATUS;
            } else if (_type == WidgetConstants::DROP_DOWN_TEXT_BOX_STRID) {
                type1 = RobotGui::WidgetConstants::DROP_DOWN_TEXT_BOX;
            } else if (_type == WidgetConstants::COMPASS_STRID) {
                type1 = RobotGui::WidgetConstants::COMPASS;
            } else if (_type == WidgetConstants::LIVE_PLOT_STRID) {
                type1 = RobotGui::WidgetConstants::LIVE_PLOT;
            } else if (_type == WidgetConstants::SETTINGS_TAB_STRID) {
                type1 = RobotGui::WidgetConstants::SETTINGS_TAB;
            } else if (_type == WidgetConstants::ATTITUDE_DISPLAY_STRID) {
                type1 = RobotGui::WidgetConstants::ATTITUDE_DISPLAY;
            }
            return type1;
        }

        inline std::string getTypeString(Type type) {
            switch (type) {
                case RobotGui::WidgetConstants::TEXT_BOX:
                    return WidgetConstants::TEXT_BOX_STRID;
                case RobotGui::WidgetConstants::VIDEO:
                    return WidgetConstants::VIDEO_STRID;
                case RobotGui::WidgetConstants::TAB:
                    return WidgetConstants::TAB_STRID;
                case RobotGui::WidgetConstants::SIMPLE_BUTTON:
                    return WidgetConstants::SIMPLE_BUTTON_STRID;
                case RobotGui::WidgetConstants::MULTI_BAR_GRAPH:
                    return WidgetConstants::MULTI_BAR_GRAPH_STRID;
                case RobotGui::WidgetConstants::ANNUNCIATOR_PANEL:
                    return WidgetConstants::ANNUNCIATOR_PANEL_STRID;
                case RobotGui::WidgetConstants::SIMPLE_CONSOLE:
                    return WidgetConstants::SIMPLE_CONSOLE_STRID;
                case RobotGui::WidgetConstants::ROV_STATUS:
                    return WidgetConstants::ROV_STATUS_STRID;
                case RobotGui::WidgetConstants::COMPLETE_CONSOLE:
                    return WidgetConstants::COMPLETE_CONSOLE_STRID;
                case RobotGui::WidgetConstants::MISSION_STATUS:
                    return WidgetConstants::MISSION_STATUS_STRID;
                case RobotGui::WidgetConstants::DROP_DOWN_TEXT_BOX:
                    return WidgetConstants::DROP_DOWN_TEXT_BOX_STRID;
                case RobotGui::WidgetConstants::COMPASS:
                    return WidgetConstants::COMPASS_STRID;
                case RobotGui::WidgetConstants::LIVE_PLOT:
                    return WidgetConstants::LIVE_PLOT_STRID;
                case RobotGui::WidgetConstants::SETTINGS_TAB:
                    return WidgetConstants::SETTINGS_TAB_STRID;
                case RobotGui::WidgetConstants::ATTITUDE_DISPLAY:
                    return WidgetConstants::ATTITUDE_DISPLAY_STRID;
                case RobotGui::WidgetConstants::NO_TYPE:
                    break;
            }
            return "";
        }
    }
    // AppConfig consts
    const char *const APP_CONFIG_FILE_PATH = "/.config/RobotGUI";
    const char *const APP_CONFIG_FILE_NAME = "/RobotGUI_Settings.csv";
    const char *const APP_CONFIG_XML_PATH = "XML_PATH";
    const char *const APP_CONFIG_NO_XML_PATH = "none";
    const char APP_CONFIG_SEP = ',';
    const char *const APP_CONFIG_ARROW_ASSET_PATH = "/arrow.png";
    const char *const APP_CONFIG_COMPASS_ASSET_PATH = "/compass.png";
    const char *const APP_CONFIG_CROSS_HAIR_ASSET_PATH = "/cross_hair.png";
    const char *const APP_CONFIG_ROLL_DIAL_ASSET_PATH = "/roll_dial_1.png";
    const char *const APP_CONFIG_ROLL_POINTER_ASSET_PATH = "/roll_pointer.png";
    const char *const ARROW_ASSET_NAME = "ARROW";
    const char *const COMPASS_ASSET_NAME = "COMPASS";
    const char *const CROSS_HAIR_ASSET_NAME = "CROSS HAIR";
    const char *const ROLL_DIAL_ASSET_NAME = "ROLL DIAL";
    const char *const ROLL_POINTER_ASSET_NAME = "ROLL POINTER";
    // Stylesheets
    const char *const TRANSPARENT_STYLE = "transparent";

    //// XML Constants ////
    namespace Xml {
        // Attributes
        const char *const WIDTH_ATR = "width";
        const char *const HEIGHT_ATR = "height";
        const char *const TYPE_ATR = "type";
        const char *const TITLE_ATR = "title";
        const char *const THEME_ATR = "theme";
        const char *const ID_ATR = "id";
        const char *const X_POS_ATR = "x";
        const char *const Y_POS_ATR = "y";
        const char *const HIDDEN_ATR = "hidden";
        const char *const DRAGGABLE_ATR = "draggable";
        const char *const STATIC_ATR = "static";
        const char *const LABEL_ATR = "label";
        const char *const VALUE_ATR = "value";
        const char *const SOURCE_ATR = "source";
        const char *const MINIMUM_ATR = "minimum";
        const char *const MAXIMUM_ATR = "maximum";
        const char *const COLOR_ATR = "color";
        const char *const ROW_NUMBER_ATR = "row_number";
        const char *const COLUMN_NUMBER_ATR = "column_number";
        const char *const SOURCE_ATTRIBUTE = "source";
        const char *const SIZE_ATR = "size";
        const char *const TRANSPARENT_ATTRIBUTE = "transparent"; //For backwards compatibility
        const char *const UPDATE_RATE_ATR = "updateRate";
        const char *const RANGE_MIN_ATR = "rangeMin";
        const char *const RANGE_MAX_ATR = "rangeMax";
        const char *const TIME_RANGE_ATR = "timeRange";
        // Style attributes
        const char *const FONT_ATR = "font";
        const char *const BACKGROUND_COLOR_ATR = "background";
        const char *const FOREGROUND_COLOR_ATR = "foreground";
        const char *const RELIEF_ATR = "relief";
        const char *const TEXT_COLOR_ATR = "textColor";
        const char *const HEADER_COLOR_ATR = "headerColor";
        const char *const FONT_SIZE_ATR = "font_size";
        const char *const BORDER_WIDTH_ATR = "borderWidth";
        // XML Tags
        const char *const WINDOW_TAG = "window";
        const char *const WIDGET_TAG = "widget";
        const char *const TAB_TAG = "tab";
        const char *const LINE_TAG = "line";
        // XML value constants
        const char *const TRUE_CONST = "true";
        const char *const TRUE_CAP_CONST = "True";
        const char *const FALSE_CONST = "false";
        const char *const FALSE_CAP_CONST = "False";
        const char *const MAX_CONST = "max";
        const int MAX_CONST_ID = -1;
        const char *const AUTO_CONST = "auto";
        const int AUTO_CONST_ID = -2;
        const char *const THEME_CONST = "theme";
        const int THEME_CONST_ID = -3;
        const char *const NONE_CONST = "none";
        const int NONE_CONST_ID = -4;
        const char *const CUSTOM_CONST = "custom";
        const int CUSTOM_CONST_ID = -5;
    }

    //// Configuration data for widgets ////
    class WidgetBaseConfig;
    struct WindowConfig {
        std::string title;
        std::string theme;
        int height;
        int width;
        int updateRate;
        std::shared_ptr<WidgetBaseConfig> firstChild;
    };
    typedef std::shared_ptr<WindowConfig> WindowConfig_ptr;

    //// Theme2 color constants ////
    namespace Themes {
        // Enum to house all possible themes
        enum Type {
            DARK,
            LIGHT,
            GREEN,
            RED,
        };
        // Used to define different formats
        struct Format {
            const char *backgroundColor;
            const char *widgetBackgroundColor;
            const char *bodyTextColor;
            const char *titleTextColor;
            const char *borderColor;
        };
        // Names of all themes
        const char *const DARK_THEME_STR = "Dark";
        const char *const LIGHT_THEME_STR = "Light";
        const char *const GREEN_THEME_STR = "Green";
        const char *const RED_THEME_STR = "Red";

    }
}

#endif //ROBOT_GUI_V3_ROBOTGUI_H
