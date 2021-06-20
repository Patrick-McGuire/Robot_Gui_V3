#ifndef ROBOT_GUI_V3_TABINFO_H
#define ROBOT_GUI_V3_TABINFO_H
#include <string>
#include <vector>
#include "WidgetInfo.h"

class TabInfo {
public:
    std::string *name;
    bool isNester;
    std::vector<TabInfo*> *nestedTabsInfo;
    std::vector<WidgetInfo*> *widgetsInfo;

    TabInfo(std::string *_name, bool _isNester);
    std::vector<WidgetInfo*>* getWidgetInfo() const;
};


#endif //ROBOT_GUI_V3_TABINFO_H
