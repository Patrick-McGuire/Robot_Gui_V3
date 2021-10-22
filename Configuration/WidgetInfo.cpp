//
// Created by patrick on 6/16/21.
//

#include "WidgetInfo.h"

#include <utility>

WidgetInfo::WidgetInfo(std::string _name, std::string _type, int _x, int _y) {
    name = std::move(_name);
    type = std::move(_type);
    x = _x;
    y = _y;
}
