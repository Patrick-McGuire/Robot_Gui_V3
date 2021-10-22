#ifndef ROBOT_GUI_V3_WIDGETINFO_H
#define ROBOT_GUI_V3_WIDGETINFO_H
#include <string>
#include <vector>

/**
 * This class is the data structure used to configure any widget. Not all fields are used for any given widget
 * The purpose of this was to make the declaration of new widgets more abstract
 */
class WidgetInfo {
public:
    std::string type;
    std::string name;
    std::vector<std::vector<std::string>> lines;
    std::string videoId;
    int x;
    int y;
    bool staticPos = false;

    WidgetInfo(std::string _name, std::string _type, int _x, int _y);
};


#endif //ROBOT_GUI_V3_WIDGETINFO_H
