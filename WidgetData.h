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

/**
 * @class WidgetData
 * Contains all data displayed and output by the widgets
 * Thread safe
 *
 * @author Patrick McGuire (Patrick-McGuire)
 */
class WidgetData {
public:
    /**
     * This contains all possible data types that can be stored in WidgetData
     */
    enum internalJsonTypes {
        int_t,
        double_t,
        bool_t,
        string_t,
        vector_t,
        map_t,
        img_t,
        none_t,
    };

    /**
     * Stores json data for a key
     * Self referencing
     */
    struct internalJSON {
        internalJsonTypes type = none_t;
        union {                             // Only one of these can be used at a time, so no need to waste memory
            int intVal = 0;
            double doubleVal;
            bool boolVal;
        };
        std::string stringVal;
        std::vector<std::shared_ptr<internalJSON>> vector;
        std::map<std::string, std::shared_ptr<internalJSON>> map;
    };
    /**
     * std::shared_ptr for internalJSON
     */
    typedef std::shared_ptr<internalJSON> internalJSON_ptr;

    //// Output ////
    /**
     * Sets a json value in the output map
     * @param key json key
     * @param val value
     */
    void setJsonOutput(const std::string &key, const internalJSON_ptr &val) {
        std::lock_guard<std::mutex> lockGuard(outJsonMutex);
        outJson[key] = val;
    }

    /**
     * Gets a json value in the output map
     * @param key json key
     * @return value
     */
    internalJSON_ptr getJsonOutput(const std::string &key) {
        std::lock_guard<std::mutex> lockGuard(outJsonMutex);
        return outJson.count(key) != 0 ? outJson[key] : std::make_shared<struct WidgetData::internalJSON>();
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
    std::map<std::string, internalJSON_ptr> *getJsonOutput() {
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
    internalJsonTypes getKeyType(const std::string &key) {
        std::lock_guard<std::mutex> lockGuard(imgMapMutex);
        std::lock_guard<std::mutex> lockGuard2(jsonMapMutex);
        return imgMap.count(key) != 0 ? img_t : jsonMap.count(key) != 0 ? jsonMap[key]->type : none_t;
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
     * Returns a string
     * @param key key to get
     * @return string
     */
    std::string getString(const std::string &key) {
        std::lock_guard<std::mutex> lockGuard(jsonMapMutex);
        return jsonMap.count(key) != 0 ? jsonMap[key]->stringVal : "";
    }

    /**
     * Returns string or default value
     * @param key key to get
     * @param _default_value value to return if key does not exist
     * @return string
     */
    std::string getString(const std::string &key, const std::string &_default_value) {
        return getKeyType(key) == string_t ? getString(key) : _default_value;
    }

    /**
     * Returns double
     * @param key to get
     * @return double
     */
    double getDouble(const std::string &key) {
        std::lock_guard<std::mutex> lockGuard(jsonMapMutex);
        return jsonMap.count(key) != 0 ? jsonMap[key]->doubleVal : 0;
    }

    /**
     * Returns double or default value
     * @param key key to get
     * @param _default_value value to return if key does not exist
     * @return double
     */
    double getDouble(const std::string &key, double _default_value) {
        return getKeyType(key) == double_t ? getDouble(key) : _default_value;
    }

    /**
     * Returns int
     * @param key key to get
     * @return int
     */
    int getInt(const std::string &key) {
        std::lock_guard<std::mutex> lockGuard(jsonMapMutex);
        return jsonMap.count(key) != 0 ? jsonMap[key]->intVal : 0;
    }

    /**
     * Returns int or default value
     * @param key key to get
     * @param _default_value value to return if key does not exist
     * @return int
     */
    int getInt(const std::string &key, int _default_value) {
        return getKeyType(key) == int_t ? getInt(key) : _default_value;
    }

    /**
     * Returns bool
     * @param key key to get
     * @return bool
     */
    bool getBool(const std::string &key) {
        std::lock_guard<std::mutex> lockGuard(jsonMapMutex);
        return jsonMap.count(key) != 0 && jsonMap[key]->boolVal;
    }

    /**
     * Returns bool or default value
     * @param key key to get
     * @param _default_value value to return if key does not exist
     * @return bool
     */
    bool getBool(const std::string &key, bool _default_value) {
        return getKeyType(key) == bool_t ? getBool(key) : _default_value;
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
    internalJSON_ptr getJSON(const std::string &key) {
        std::lock_guard<std::mutex> lockGuard(jsonMapMutex);
        return jsonMap.count(key) != 0 ? jsonMap[key] : std::make_shared<struct WidgetData::internalJSON>();
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
    void setJSON(const std::string &key, const internalJSON_ptr &val) {
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

    /**
     * Prints out a internalJSON_ptr
     * @param json json to print
     */
    static void printJSON(internalJSON_ptr json, int level = 0);

    static internalJSON_ptr getJSONObjectFromString(std::string _string) {
        WidgetData::internalJSON_ptr out = std::make_shared<struct WidgetData::internalJSON>();
        out->stringVal = std::move(_string);
        out->type = WidgetData::string_t;
        return out;
    }

    static internalJSON_ptr getJSONObjectFromInt(int _int) {
        WidgetData::internalJSON_ptr out = std::make_shared<struct WidgetData::internalJSON>();
        out->intVal = _int;
        out->type = WidgetData::int_t;
        return out;
    }

private:
    // Data in storage
    std::mutex imgMapMutex;
    std::mutex jsonMapMutex;
    std::mutex keysUpdatedMutex;
    std::map<std::string, cv::Mat> imgMap;
    std::map<std::string, internalJSON_ptr> jsonMap;
    std::map<std::string, bool> keysUpdated;
    // Data out storage
    std::mutex outFlagsMutex;
    std::mutex outJsonMutex;
    std::map<std::string, bool> outFlags;
    std::map<std::string, internalJSON_ptr> outJson;
    // Operation
    std::mutex guiActiveMutex;
    bool guiActive = true;
};


#endif //ROBOT_GUI_V3_WIDGETDATA_H
