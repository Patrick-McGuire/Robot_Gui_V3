//
// Created by patrick on 11/5/21.
//

#ifndef ROBOT_GUI_V3_CONFIGSTRUCTS_H
#define ROBOT_GUI_V3_CONFIGSTRUCTS_H

#include <string>
#include <vector>

struct WidgetConfig {
    std::string title;
    std::string type;
    std::string id;
    int x;
    int y;
    bool hidden;
    bool draggable;
    /////// Widget specific ///////
    // Tab widget collection
    std::vector<std::string> tabNames;
    std::vector<std::vector<struct WidgetConfig*>> tabWidgets;
    // Configurable textbox widget
    std::vector<std::vector<std::string>> lines;
};

struct WindowConfig {
    std::string title;
    std::string theme;
    int height;
    int width;
    struct WidgetConfig *firstChild;
};

#endif //ROBOT_GUI_V3_CONFIGSTRUCTS_H
