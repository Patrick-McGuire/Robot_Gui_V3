#ifndef ROBOT_GUI_V3_WIDGETINFO_H
#define ROBOT_GUI_V3_WIDGETINFO_H
#include <string>
#include <vector>

/**
 * This class is the data structure used to configure any widget. Not all feilds are used for any given widget
 * The purpose of this was to make the declaration of new widgets more abstract
 */
class WidgetInfo {
public:
    std::string *name;
    std::vector<std::vector<std::string>> lines;
    int x;
    int y;

    WidgetInfo(std::string *_name, int _x, int _y);
};


#endif //ROBOT_GUI_V3_WIDGETINFO_H
