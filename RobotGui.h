#ifndef ROBOT_GUI_V3_ROBOTGUI_H
#define ROBOT_GUI_V3_ROBOTGUI_H

#include <string>
#include <vector>
#include "XML/AppConfig.h"
#include "array"

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
    // Used to control when the GUI updates data
    enum GuiRunState {
        UPDATE_ON_POST,
        UPDATE_PERIODIC,
        UPDATE_PERIODIC_AND_ON_POST,
    };

    //// Constants ////
    // Widget types
    const char *const TEXT_BOX_WIDGET_STRID = "textBox";
    const char *const VIDEO_WIDGET_STRID = "video";
    const char *const TAB_WIDGET_STRID = "tab";
    const char *const SIMPLE_BUTTON_WIDGET_STRID = "simpleButton";
    const char *const MULTI_BAR_GRAPH_STRID = "multiBarGraph";
    const char *const ANNUNCIATOR_PANEL_STRID = "annunciatorPanel";
    const char *const SIMPLE_CONSOLE_WIDGET_STRID = "simpleConsole";
    // AppConfig consts
    const char *const APP_CONFIG_FILE_PATH = "/.config/RobotGUI";
    const char *const APP_CONFIG_FILE_NAME = "/RobotGUI_Settings.csv";
    const char *const APP_CONFIG_XML_PATH = "XML_PATH";
    const char *const APP_CONFIG_NO_XML_PATH = "none";
    const char APP_CONFIG_SEP = ',';
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
        const char *const ROW_NUMBER_ATTRIBUTE = "row_number";
        const char *const COLUMN_NUMBER_ATTRIBUTE = "column_number";
        const char *const SOURCE_ATTRIBUTE = "source";
        // Style attributes
        const char *const FONT_ATR = "font";
        const char *const BACKGROUND_COLOR_ATR = "background";
        const char *const FOREGROUND_COLOR_ATR = "foreground";
        const char *const RELIEF_ATR = "relief";
        const char *const TEXT_COLOR_ATR = "textColor";
        const char *const HEADER_COLOR_ATR = "headerColor";
        const char *const FONT_SIZE_ATR = "fontSize";
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
    }

    //// Configuration data for widgets ////
    // Data for each line of MultiBarGraph
    struct GraphLineConfig {
        std::string type;
        std::string source;
        std::string title;
        double min;
        double max;
        std::string colorString;
    };
    // Data for every widget
    struct WidgetConfig {
        std::string title;
        std::string type;
        std::string id;
        std::string objectName;         // Not set by XML parser
        int x;
        int y;
        int height;
        int width;
        bool hidden;
        bool draggable;
        bool staticPos;
        std::string source;
        ////// Style //////
        std::string font;
        std::string backgroundColor;
        std::string foregroundColor;
        std::string relief;
        std::string textColor;
        std::string headerColor;
        int fontSize;
        int borderWidth;
        /////// Widget specific ///////
        // Tab widget collection
        std::vector<std::string> tabNames;
        std::vector<std::vector<std::shared_ptr<WidgetConfig>>> tabWidgets;
        // Configurable textbox widget
        std::vector<std::vector<std::string>> lines;
        // Configurable bar graph widget
        std::vector<GraphLineConfig> graphLines;
        // Annunciator Panel
        int rowNumber;
        int columnNumber;
    };
    typedef std::shared_ptr<WidgetConfig> WidgetConfig_ptr;
    // Window configuration data
    struct WindowConfig {
        std::string title;
        std::string theme;
        int height;
        int width;
        WidgetConfig_ptr firstChild;
    };
    typedef std::shared_ptr<WindowConfig> WindowConfig_ptr;

    //// Theme2 color constants ////
    namespace Themes {
        // Enum to house all possible themes
        enum Type {
            DARK,
            LIGHT,
            GREEN,
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

    }
}

#endif //ROBOT_GUI_V3_ROBOTGUI_H
