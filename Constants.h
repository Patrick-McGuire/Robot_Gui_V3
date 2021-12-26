#ifndef ROBOT_GUI_V3_CONSTANTS_H
#define ROBOT_GUI_V3_CONSTANTS_H

// Widget types
#define textBoxWidgetSTRID "textBox"
#define videoWidgetSTRID "video"
#define tabWidgetSTRID "tab"
#define SIMPLE_BUTTON_WIDGET_STRID "simpleButton"
#define MULTI_BAR_GRAPH_STRID "multiBarGraph"

// AppConfig consts
#define appConfigFilePath "/.config/RobotGUI"
#define appConfigFileName "/RobotGUI_Settings.csv"
#define appConfigXmlPath "XML_PATH"
#define appConfigSep ','
#define appConfigNoXmlPath "none"

// Custom messageTypes
enum MessageType {
    JSON=3,
    IMG=4,
};

enum ReturnType {
    None=0,
    Flags=1,
    Values=2,
    FlagsAndValues=3,
};

enum GuiRunState {
    updateOnPost,
    updatePeriodic,
    updatePeriodicOnPost,
};

#endif //ROBOT_GUI_V3_CONSTANTS_H
