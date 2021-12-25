#ifndef ROBOT_GUI_V3_BASEINTERFACE_H
#define ROBOT_GUI_V3_BASEINTERFACE_H

#include "iostream"
#include <vector>
#include "../WidgetData.h"
#include "../CoreGUI.h"
#include "../Constants.h"
#include "thread"
#include "opencv2/opencv.hpp"

class CoreGUI;

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
     * @param coreGui CoreGUI object to interface with
     */
    explicit BaseInterface(CoreGUI *coreGui);

    /**
     * Finds the type of data for a given key
     * @param key
     * @return data type <string>
     */
    WidgetData::internalJsonTypes getKeyType(const std::string& key) {
        return widgetData->getKeyType(key);
    }

    /**
     * Returns if the GUI is active
     * @return if active
     */
    bool isActive() {
        return widgetData->getGuiActive();
    }

    /**
     * Sets a img
     * @param key key for the img
     * @param img img to set
     */
    void setImg(const std::string& key, const cv::Mat &img) {
        widgetData->setImg(key, img);
    }

    /**
     * Sets a json value
     * @param key key for the json value
     * @param val value, internalJSON_ptr
     */
    void setJSON(const std::string &key, const WidgetData::internalJSON_ptr &val) {
        widgetData->setJSON(key, val);
    }

    /**
     * Sets a boolean in the json map
     * @param key key to set
     * @param val value
     */
    void setBool(const std::string &key, bool val) {
        auto currentKeyType = widgetData->getKeyType(key);
        auto json = widgetData->getJSON(key);
        json->boolVal = val;
        json->type = WidgetData::bool_t;
        if(currentKeyType == WidgetData::img_t || currentKeyType == WidgetData::none_t) {
            widgetData->setJSON(key, json);
        } else {
            widgetData->setKeyUpdated(key);
        }
    }

    /**
     * Sets a int in the json map
     * @param key key to set
     * @param val value
     */
    void setInt(const std::string &key, int val) {
        auto currentKeyType = widgetData->getKeyType(key);
        auto json = widgetData->getJSON(key);
        json->intVal = val;
        json->type = WidgetData::int_t;
        if(currentKeyType == WidgetData::img_t || currentKeyType == WidgetData::none_t) {
            widgetData->setJSON(key, json);
        } else {
            widgetData->setKeyUpdated(key);
        }
    }

    /**
     * Sets a double in the json map
     * @param key key to set
     * @param val value
     */
    void setDouble(const std::string &key, double val) {
        auto currentKeyType = widgetData->getKeyType(key);
        auto json = widgetData->getJSON(key);
        json->doubleVal = val;
        json->type = WidgetData::double_t;
        if(currentKeyType == WidgetData::img_t || currentKeyType == WidgetData::none_t) {
            widgetData->setJSON(key, json);
        } else {
            widgetData->setKeyUpdated(key);
        }
    }

    /**
     * Sets a string in the json map
     * @param key key to set
     * @param val value
     */
    void setString(const std::string &key, const std::string &val) {
        auto currentKeyType = widgetData->getKeyType(key);
        auto json = widgetData->getJSON(key);
        json->stringVal = val;
        json->type = WidgetData::string_t;
        if(currentKeyType == WidgetData::img_t || currentKeyType == WidgetData::none_t) {
            widgetData->setJSON(key, json);
        } else {
            widgetData->setKeyUpdated(key);
        }
    }

    /**
     * Returns bool
     * @param key key to get
     * @return bool
     */
    bool getBool(const std::string& key) {
        return widgetData->getBool(key);
    }

    /**
     * Returns int
     * @param key key to get
     * @return int
     */
    int getInt(const std::string& key) {
        return widgetData->getInt(key);
    }

    /**
     * Returns double
     * @param key to get
     * @return double
     */
    double getDouble(const std::string& key) {
        return widgetData->getDouble(key);
    }

    /**
     * Returns a string
     * @param key key to get
     * @return string
     */
    std::string getString(const std::string& key) {
        return widgetData->getString(key);
    }

    /**
     * Returns a img
     * @param key key to get
     * @return img
     */
    cv::Mat getImg(const std::string &key) {
        return widgetData->getImg(key);
    }

    /**
     * Returns a json value object (internalJSON_ptr)
     * @param key key to get
     * @return json object
     */
    WidgetData::internalJSON_ptr getJSON(const std::string &key) {
        return widgetData->getJSON(key);
    }

private:
    WidgetData *widgetData;
};


#endif //ROBOT_GUI_V3_BASEINTERFACE_H
