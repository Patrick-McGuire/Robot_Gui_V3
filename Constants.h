#ifndef ROBOT_GUI_V3_CONSTANTS_H
#define ROBOT_GUI_V3_CONSTANTS_H

// Widget types
#define textBoxWidgetSTRID "textBox"
#define videoWidgetSTRID "video"
#define tabWidgetSTRID "tab"
#define SIMPLE_BUTTON_WIDGET_STRID "simpleButton"

// WidgetData types
#define intType "int"
#define doubleType "double"
#define boolType "bool"
#define stringType "string"
#define imgType "img"
#define jsonType "json"
#define noType "none"

// AppConfig consts
#define appConfigFilePath "/.config/RobotGUI"
#define appConfigFileName "/RobotGUI_Settings.csv"
#define appConfigXmlPath "XML_PATH"
#define appConfigSep ','
#define appConfigNoXmlPath "none"

// Custom messageTypes
enum MessageType {
    String=0,
    Int=1,
    Float=2,
    JSON=3,
    IMG=4,
};


#endif //ROBOT_GUI_V3_CONSTANTS_H
