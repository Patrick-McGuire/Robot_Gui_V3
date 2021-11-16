//
// Created by patrick on 11/5/21.
//

#ifndef ROBOT_GUI_V3_CONFIGSTRUCTS_H
#define ROBOT_GUI_V3_CONFIGSTRUCTS_H

#include <string>
#include <vector>
#include "XML/AppConfig.h"

struct WidgetConfig {
    std::string title;
    std::string type;
    std::string id;
    std::string objectName;
    int x;
    int y;
    int height;
    int width;
    bool hidden;
    bool draggable;
    bool staticPos;
    /////// Widget specific ///////
    // Tab widget collection
    std::vector<std::string> tabNames;
    std::vector<std::vector<std::shared_ptr<WidgetConfig>>> tabWidgets;
    // Configurable textbox widget
    std::vector<std::vector<std::string>> lines;
};

typedef std::shared_ptr<WidgetConfig> WidgetConfig_ptr;

struct WindowConfig {
    std::string title;
    std::string theme;
    int height;
    int width;
    WidgetConfig_ptr firstChild;
};

typedef std::shared_ptr<WindowConfig> WindowConfig_ptr;




#endif //ROBOT_GUI_V3_CONFIGSTRUCTS_H
