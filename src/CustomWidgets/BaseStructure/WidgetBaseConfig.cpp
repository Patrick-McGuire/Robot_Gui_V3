#include "WidgetBaseConfig.h"
#include "../../RobotGui.h"

RobotGui::WidgetType RobotGui::WidgetBaseConfig::getType(const std::string &_type) {
    WidgetType type1 = NO_TYPE;
    if (_type == RobotGui::TEXT_BOX_WIDGET_STRID) {
        type1 = TEXT_BOX;
    } else if (_type == RobotGui::VIDEO_WIDGET_STRID) {
        type1 = VIDEO;
    } else if (_type == RobotGui::TAB_WIDGET_STRID) {
        type1 = TAB;
    } else if (_type == RobotGui::SIMPLE_BUTTON_WIDGET_STRID) {
        type1 = SIMPLE_BUTTON;
    } else if (_type == RobotGui::MULTI_BAR_GRAPH_STRID) {
        type1 = MULTI_BAR_GRAPH;
    } else if (_type == RobotGui::ANNUNCIATOR_PANEL_STRID) {
        type1 = ANNUNCIATOR_PANEL;
    } else if (_type == RobotGui::SIMPLE_CONSOLE_WIDGET_STRID) {
        type1 = SIMPLE_CONSOLE;
    } else if (_type == RobotGui::ROV_STATUS_WIDGET_STRID) {
        type1 = ROV_STATUS;
    } else if (_type == RobotGui::COMPLETE_CONSOLE_WIDGET_STRID) {
        type1 = COMPLETE_CONSOLE;
    } else if (_type == RobotGui::MISSION_STATUS_WIDGET_STRID) {
        type1 = MISSION_STATUS;
    } else if (_type == RobotGui::DROP_DOWN_TEXT_BOX_WIDGET_STRID) {
        type1 = DROP_DOWN_TEXT_BOX;
    } else if (_type == RobotGui::COMPASS_WIDGET_STRID) {
        type1 = COMPASS;
    } else if (_type == RobotGui::LIVE_PLOT_WIDGET_STRID) {
        type1 = LIVE_PLOT;
    } else if(_type == RobotGui::SETTINGS_TAB_STRID) {
        type1 = SETTINGS_TAB;
    }
    return type1;
}

std::string RobotGui::WidgetBaseConfig::getTypeString() const {
    switch (type) {
        case TEXT_BOX:
            return RobotGui::TAB_WIDGET_STRID;
        case VIDEO:
            return RobotGui::VIDEO_WIDGET_STRID;
        case TAB:
            return RobotGui::TAB_WIDGET_STRID;
        case SIMPLE_BUTTON:
            return RobotGui::SIMPLE_BUTTON_WIDGET_STRID;
        case MULTI_BAR_GRAPH:
            return RobotGui::MULTI_BAR_GRAPH_STRID;
        case ANNUNCIATOR_PANEL:
            return RobotGui::ANNUNCIATOR_PANEL_STRID;
        case SIMPLE_CONSOLE:
            return RobotGui::SIMPLE_CONSOLE_WIDGET_STRID;
        case ROV_STATUS:
            return RobotGui::ROV_STATUS_WIDGET_STRID;
        case COMPLETE_CONSOLE:
            return RobotGui::COMPLETE_CONSOLE_WIDGET_STRID;
        case MISSION_STATUS:
            return RobotGui::MISSION_STATUS_WIDGET_STRID;
        case DROP_DOWN_TEXT_BOX:
            return RobotGui::DROP_DOWN_TEXT_BOX_WIDGET_STRID;
        case COMPASS:
            return RobotGui::COMPASS_WIDGET_STRID;
        case LIVE_PLOT:
            return RobotGui::LIVE_PLOT_WIDGET_STRID;
        case SETTINGS_TAB:
            return RobotGui::SETTINGS_TAB_STRID;
        case NO_TYPE:
            break;
    }
    return "";
}

RobotGui::WidgetBaseConfig::SharedPtr RobotGui::WidgetBaseConfig::create(const std::string &_type) {
    return RobotGui::WidgetBaseConfig::SharedPtr(new WidgetBaseConfig(getType(_type)));
}

RobotGui::WidgetBaseConfig::SharedPtr RobotGui::WidgetBaseConfig::create(RobotGui::WidgetType _type) {
    return RobotGui::WidgetBaseConfig::SharedPtr(new WidgetBaseConfig(_type));
}

RobotGui::WidgetBaseConfig::SharedPtr RobotGui::WidgetBaseConfig::create() {
    return RobotGui::WidgetBaseConfig::SharedPtr(new WidgetBaseConfig(NO_TYPE));
}

RobotGui::WidgetBaseConfig::WidgetBaseConfig(RobotGui::WidgetType _type) : type(_type) {

}

void RobotGui::WidgetBaseConfig::showEditMenu() {

}

void RobotGui::WidgetBaseConfig::onEdit() {

}



