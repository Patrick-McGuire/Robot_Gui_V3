#ifndef ROBOT_GUI_V3_BASEINTERFACE_H
#define ROBOT_GUI_V3_BASEINTERFACE_H

#include "iostream"
#include <vector>
#include "../WidgetData.h"
#include "../CoreGUI.h"
#include "../Constants.h"
#include "thread"
#include "opencv2/opencv.hpp"

/**
 * @class WidgetData
 * Wrapper for WidgetData to be used by Interfaces
 *
 * @author Patrick McGuire (Patrick-McGuire)
 */
class BaseInterface {
public:
    /**
     * Constructor
     * @param _widgetData WidgetData object to wrap
     */
    explicit BaseInterface(CoreGUI *coreGui) {
        widgetData = coreGui->getWidgetData();
    }

    WidgetData::internalJsonTypes getKeyType(const std::string& key) {
        return widgetData->getKeyType(key);
    }

    void setBool(const std::string &key, bool val) {
        auto currentKeyType = widgetData->getKeyType(key);
        auto json = widgetData->getJSON(key);
        json->boolVal = val;
        if(currentKeyType == WidgetData::img_t || currentKeyType == WidgetData::none_t) {
            widgetData->setJSON(key, json);
        } else {
            widgetData->setKeyUpdated(key);
        }
    }

    void setInt(const std::string &key, int val) {
        auto currentKeyType = widgetData->getKeyType(key);
        auto json = widgetData->getJSON(key);
        json->intVal = val;
        if(currentKeyType == WidgetData::img_t || currentKeyType == WidgetData::none_t) {
            widgetData->setJSON(key, json);
        } else {
            widgetData->setKeyUpdated(key);
        }
    }

    void setDouble(const std::string &key, double val) {
        auto currentKeyType = widgetData->getKeyType(key);
        auto json = widgetData->getJSON(key);
        json->doubleVal = val;
        if(currentKeyType == WidgetData::img_t || currentKeyType == WidgetData::none_t) {
            widgetData->setJSON(key, json);
        } else {
            widgetData->setKeyUpdated(key);
        }
    }
    void setString(const std::string &key, const std::string &val) {
        auto currentKeyType = widgetData->getKeyType(key);
        auto json = widgetData->getJSON(key);
        json->stringVal = val;
        if(currentKeyType == WidgetData::img_t || currentKeyType == WidgetData::none_t) {
            widgetData->setJSON(key, json);
        } else {
            widgetData->setKeyUpdated(key);
        }
    }

    bool getBool(const std::string& key) {
        return widgetData->getBool(key);
    }

    int getInt(const std::string& key) {
        return widgetData->getInt(key);
    }

    double getDouble(const std::string& key) {
        return widgetData->getDouble(key);
    }

    std::string getString(const std::string& key) {
        return widgetData->getString(key);
    }



private:
    WidgetData *widgetData;
};


#endif //ROBOT_GUI_V3_BASEINTERFACE_H
