#ifndef ROBOT_GUI_V3_CONSTANTS_H
#define ROBOT_GUI_V3_CONSTANTS_H

// Widget types
#define TEXT_BOX_WIDGET_STRID "textBox"
#define VIDEO_WIDGET_STRID "video"
#define TAB_WIDGET_STRID "tab"
#define SIMPLE_BUTTON_WIDGET_STRID "simpleButton"
#define MULTI_BAR_GRAPH_STRID "multiBarGraph"

// AppConfig consts
#define APP_CONFIG_FILE_PATH "/.config/RobotGUI"
#define APP_CONFIG_FILE_NAME "/RobotGUI_Settings.csv"
#define APP_CONFIG_XML_PATH "XML_PATH"
#define APP_CONFIG_SEP ','
#define APP_CONFIG_NO_XML_PATH "none"

// Custom messageTypes
enum MessageType {
    JSON=3,
    IMG=4,
};

enum ReturnType {
    NO_RETURN=0,
    RETURN_FLAGS=1,
    RETURN_VALUES=2,
    RETURN_FLAGS_AND_VALUES=3,
};

enum GuiRunState {
    UPDATE_ON_POST,
    UPDATE_PERIODIC,
    UPDATE_PERIODIC_ON_POST,
};

#endif //ROBOT_GUI_V3_CONSTANTS_H
