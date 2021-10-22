#include "TabInfo.h"

#include <utility>


TabInfo::TabInfo(std::string _name, bool _isNester) {
    name = std::move(_name);
    isNester = _isNester;
    widgetsInfo = new std::vector<WidgetInfo*>;
    nestedTabsInfo = new std::vector<TabInfo*>;
}

std::vector<WidgetInfo*>* TabInfo::getWidgetInfo() const {
    return widgetsInfo;
}

