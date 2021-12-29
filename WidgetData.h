#ifndef ROBOT_GUI_V3_WIDGETDATA_H
#define ROBOT_GUI_V3_WIDGETDATA_H

#include <map>
#include "RobotGui.h"
#include <vector>
#include "opencv2/opencv.hpp"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "thread"
#include "mutex"
#include "Theme.h"
#include "InternalJson.h"

/**
 * @class WidgetData
 * Contains all data displayed and output by the widgets
 * Thread safe
 *
 * @author Patrick McGuire (Patrick-McGuire)
 */
class WidgetData {
public:
//    enum Types {
//        json_t,
//        img_t,
//        none_t,
//    };


    //// Output ////
    /**
     * Sets a json value in the output map
     * @param key json key
     * @param val value
     */
    void setJsonOutput(const std::string &key, const InternalJson::SharedPtr &val) {
        std::lock_guard<std::mutex> lockGuard(outJsonMutex);
        outJson[key] = val;
    }

    /**
     * Gets a json value in the output map
     * @param key json key
     * @return value
     */
    InternalJson::SharedPtr getJsonOutput(const std::string &key) {
        std::lock_guard<std::mutex> lockGuard(outJsonMutex);
        return outJson.count(key) != 0 ? outJson[key] : InternalJson::create();
    }

    /**
     * Sets a flag high in the output flags
     * @param key key to set high
     */
    void raiseOutputFlag(const std::string &key) {
        std::lock_guard<std::mutex> lockGuard(outFlagsMutex);
        outFlags[key] = true;
    }

    /**
     * Sets a flag low in the output flags
     * @param key key to set low
     */
    void clearOutputFlag(const std::string &key) {
        std::lock_guard<std::mutex> lockGuard(outFlagsMutex);
        outFlags[key] = false;
    }

    /**
     * Gets the entire return json data map
     * @return output json map
     */
    std::map<std::string, InternalJson::SharedPtr> *getJsonOutput() {
        std::lock_guard<std::mutex> lockGuard(outJsonMutex);
        return &outJson;
    }

    /**
     * Gets the entire return flags data map
     * @return output flags map
     */
    std::map<std::string, bool> *getFlagOutput() {
        std::lock_guard<std::mutex> lockGuard(outFlagsMutex);
        return &outFlags;
    }

    /**
     * Gets a output flag
     * @param key key to get
     * @return flag value
     */
    bool getFlagOutput(const std::string &key) {
        std::lock_guard<std::mutex> lockGuard(outFlagsMutex);
        return outFlags.count(key) != 0 && outFlags[key];
    }

    /**
     * Gets if a key exists in the output flags map
     * @param key key to check
     * @return if key exists
     */
    bool outputFlagExists(const std::string &key) {
        std::lock_guard<std::mutex> lockGuard(outFlagsMutex);
        return outFlags.count(key) != 0;
    }

    /**
     * Gets if a key exists in the output json map
     * @param key key to check
     * @return if key exists
     */
    bool outputJsonExists(const std::string &key) {
        std::lock_guard<std::mutex> lockGuard(jsonMapMutex);
        return outJson.count(key) != 0;
    }

    //// Input ////
    /**
     * Finds the type of data for a given key
     * @param key
     * @return data type <string>
     */
    InternalJson::Types getJsonKeyType(const std::string &key) {
//        std::lock_guard<std::mutex> lockGuard(imgMapMutex);
        std::lock_guard<std::mutex> lockGuard2(jsonMapMutex);
        return jsonMap.count(key) != 0 ? jsonMap[key]->getType() : InternalJson::none_t;
//        return imgMap.count(key) != 0 ? img_t : jsonMap.count(key) != 0 ? json_t : none_t;
    }

    /**
     * Lowers all updated flags for keys
     */
    void resetKeysUpdated() {
        std::lock_guard<std::mutex> lockGuard(keysUpdatedMutex);
        for (auto &it : keysUpdated) {
            keysUpdated[it.first] = false;
        }
    }

    /**
     * Returns if a key has been updated
     * @param key key to check
     * @return if key has been updated
     */
    bool keyUpdated(const std::string &key) {
        std::lock_guard<std::mutex> lockGuard(keysUpdatedMutex);
        return keysUpdated[key];
    }

    bool keyUpdated() {
        std::lock_guard<std::mutex> lockGuard(keysUpdatedMutex);
        for (auto &it : keysUpdated) {
            if (keysUpdated[it.first]) {
                return true;
            }
        }
        return false;
    }

    /**
     * Returns if a key corresponds to a img
     * @param key key to check
     * @return if key exists
     */
    bool imgExits(const std::string &key) {
        std::lock_guard<std::mutex> lockGuard(imgMapMutex);
        return imgMap.count(key) != 0;
    }

    /**
     * Returns if a key corresponds to a json
     * @param key key to check
     * @return if key exists
     */
    bool jsonExists(const std::string &key) {
        std::lock_guard<std::mutex> lockGuard(jsonMapMutex);
        return jsonMap.count(key) != 0;
    }

    /**
     * Returns a string
     * @param key key to get
     * @param defaultVal value to return if key does not exist
     * @return string
     */
    std::string getString(const std::string &key, const std::string &defaultVal = "") {
        std::lock_guard<std::mutex> lockGuard(jsonMapMutex);
        return jsonMap.count(key) != 0 ? jsonMap[key]->getString(defaultVal) : defaultVal;
    }

    /**
     * Returns double
     * @param key to get
     * @param defaultVal value to return if key does not exist
     * @return double
     */
    double getDouble(const std::string &key, double defaultVal=0) {
        std::lock_guard<std::mutex> lockGuard(jsonMapMutex);
        return jsonMap.count(key) != 0 ? jsonMap[key]->getDouble(defaultVal) : defaultVal;
    }

    /**
     * Returns int
     * @param key key to get
     * @param defaultVal value to return if key does not exist
     * @return int
     */
    int getInt(const std::string &key, int defaultVal=0) {
        std::lock_guard<std::mutex> lockGuard(jsonMapMutex);
        return jsonMap.count(key) != 0 ? jsonMap[key]->getInt(defaultVal) : defaultVal;
    }

    /**
     * Returns bool
     * @param key key to get
     * @param defaultVal value to return if key does not exist
     * @return bool
     */
    bool getBool(const std::string &key, bool defaultVal=false) {
        std::lock_guard<std::mutex> lockGuard(jsonMapMutex);
        return jsonMap.count(key) != 0 ? jsonMap[key]->getBool(defaultVal) : defaultVal;
    }

    /**
     * Returns a img
     * @param key key to get
     * @return img
     */
    cv::Mat getImg(const std::string &key) {
        std::lock_guard<std::mutex> lockGuard(imgMapMutex);
        return imgMap[key];
    }

    /**
     * Returns a json value object (internalJSON_ptr)
     * @param key key to get
     * @return json object
     */
    InternalJson::SharedPtr getJSON(const std::string &key) {
        std::lock_guard<std::mutex> lockGuard(jsonMapMutex);
        return jsonMap.count(key) != 0 ? jsonMap[key] : InternalJson::create();
    }

    /**
     * Sets a img
     * @param key key for the img
     * @param img img to set
     */
    void setImg(const std::string &key, cv::Mat img) {
        std::lock_guard<std::mutex> lockGuard(keysUpdatedMutex);
        std::lock_guard<std::mutex> lockGuard2(imgMapMutex);
        keysUpdated[key] = true;
        imgMap[key] = std::move(img);
    }

    /**
     * Sets a json value
     * @param key key for the json value
     * @param val value, internalJSON_ptr
     */
    void setJSON(const std::string &key, const InternalJson::SharedPtr &val) {
        std::lock_guard<std::mutex> lockGuard(keysUpdatedMutex);
        std::lock_guard<std::mutex> lockGuard2(jsonMapMutex);
        keysUpdated[key] = true;
        jsonMap[key] = val;
    }

    /**
     * Saves the key type
     * @param key
     * @param keyType
     */
    void setKeyUpdated(const std::string &key) {
        std::lock_guard<std::mutex> lockGuard(keysUpdatedMutex);
        keysUpdated[key] = true;
    }

    /**
     * Signals to any threads listening to end
     */
    void endGui() {
        std::lock_guard<std::mutex> lockGuard(guiActiveMutex);
        guiActive = false;
    }

    /**
     * Returns if the GUI is active
     * @return if active
     */
    bool getGuiActive() {
        std::lock_guard<std::mutex> lockGuard(guiActiveMutex);
        return guiActive;
    }

private:
    // Data in storage
    std::mutex imgMapMutex;
    std::mutex jsonMapMutex;
    std::mutex keysUpdatedMutex;
    std::map<std::string, cv::Mat> imgMap;
    std::map<std::string, InternalJson::SharedPtr> jsonMap;
    std::map<std::string, bool> keysUpdated;
    // Data out storage
    std::mutex outFlagsMutex;
    std::mutex outJsonMutex;
    std::map<std::string, bool> outFlags;
    std::map<std::string, InternalJson::SharedPtr> outJson;
    // Operation
    std::mutex guiActiveMutex;
    bool guiActive = true;
};


#endif //ROBOT_GUI_V3_WIDGETDATA_H
