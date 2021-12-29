#ifndef ROBOT_GUI_V3_BASEINTERFACE_H
#define ROBOT_GUI_V3_BASEINTERFACE_H

#include "iostream"
#include <vector>
#include "../WidgetData.h"
#include "../RobotGui.h"
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
     */
    explicit BaseInterface();

    /**
     * Initializes the interface
     * @param _widgetData WidgetData to interface with
     */
    void setWidgetData(WidgetData *_widgetData);

    /**
     * Finds the type of data for a given key
     * @param key
     * @return data type <string>
     */
    WidgetData::Types getKeyType(const std::string &key);

    /**
     * Returns if the GUI is active
     * @return if active
     */
    bool isActive();

    /**
     * Sets a img
     * @param key key for the img
     * @param img img to set
     */
    void setImg(const std::string &key, const cv::Mat &img);

    /**
     * Sets a json value
     * @param key key for the json value
     * @param val value, internalJSON_ptr
     */
    void setJSON(const std::string &key, const InternalJson::SharedPtr &val);

    /**
     * Sets a boolean in the json map
     * @param key key to set
     * @param val value
     */
    void setBool(const std::string &key, bool val);

    /**
     * Sets a int in the json map
     * @param key key to set
     * @param val value
     */
    void setInt(const std::string &key, int val);

    /**
     * Sets a double in the json map
     * @param key key to set
     * @param val value
     */
    void setDouble(const std::string &key, double val);

    /**
     * Sets a string in the json map
     * @param key key to set
     * @param val value
     */
    void setString(const std::string &key, const std::string &val);

    /**
     * Returns bool
     * @param key key to get
     * @return bool
     */
    bool getBool(const std::string &key);

    /**
     * Returns int
     * @param key key to get
     * @return int
     */
    int getInt(const std::string &key);

    /**
     * Returns double
     * @param key to get
     * @return double
     */
    double getDouble(const std::string &key);

    /**
     * Returns a string
     * @param key key to get
     * @return string
     */
    std::string getString(const std::string &key);

    /**
     * Returns a img
     * @param key key to get
     * @return img
     */
    cv::Mat getImg(const std::string &key);

    /**
     * Returns a json value object (internalJSON_ptr)
     * @param key key to get
     * @return json object
     */
    InternalJson::SharedPtr getJSON(const std::string &key);

    /**
     * Gets if a key exists in the output flags map
     * @param key key to check
     * @return if key exists
     */
    bool outputFlagExists(const std::string &key);

    /**
     * Gets a output flag
     * @param key key to get
     * @return flag value
     */
    bool getFlagOutput(const std::string &key);

    /**
     * Gets the entire return flags data map
     * @return output flags map
     */
    std::map<std::string, bool> *getFlagOutput();

    /**
     * Sets a flag low in the output flags
     * @param key key to set low
     */
    void clearOutputFlag(const std::string &key);

private:
    WidgetData *widgetData;
};


#endif //ROBOT_GUI_V3_BASEINTERFACE_H
