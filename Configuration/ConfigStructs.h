//
// Created by patrick on 11/5/21.
//

#ifndef ROBOT_GUI_V3_CONFIGSTRUCTS_H
#define ROBOT_GUI_V3_CONFIGSTRUCTS_H

#include <string>
#include <vector>

struct WidgetConfig {
    std::string name;
    std::string title;
    std::string type;
    std::string id;
    int x;
    int y;
    bool hidden;
    bool draggable;
    std::vector<struct WidgetConfig*> widgets;
};

struct WindowConfig {
    std::string title;
    std::string theme;
    int height;
    int width;
    struct WidgetConfig *config;
};

#endif //ROBOT_GUI_V3_CONFIGSTRUCTS_H
