#ifndef ROBOT_GUI_V3_WIDGETDATA_H
#define ROBOT_GUI_V3_WIDGETDATA_H
#include <map>
#include "Constants.h"
#include <vector>
#include "opencv2/opencv.hpp"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"

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
     */
    struct internalJSON {
        internalJsonTypes type;
        int intVal;
        double doubleVal;
        bool boolVal;
        std::string stringVal;
        std::vector<std::shared_ptr<internalJSON>> vector;
        std::map<std::string, std::shared_ptr<internalJSON>> map;
    };
    /**
     * std::shared_ptr for internalJSON
     */
    typedef std::shared_ptr<internalJSON> internalJSON_ptr;

private:
    std::map<std::string, cv::Mat> imgMap;
    std::map<std::string, internalJSON_ptr> jsonMap;
    std::map<std::string, bool> keysUpdated;
    /**
     * Saves the key type
     * @param key
     * @param keyType
     */
    void setKeyUpdated(const std::string& key, const std::string& keyType);

public:
    /**
     * Finds the type of data for a given key
     * @param key
     * @return data type <string>
     */
    internalJsonTypes getKeyType(const std::string& key);

    /**
     * Lowers all updated flags for keys
     */
    void resetKeysUpdated();

    /**
     * Returns if a key has been updated
     * @param key key to check
     * @return if key has been updated
     */
    bool keyUpdated(const std::string& key);

    /**
     * Returns if a key corresponds to a img
     * @param key key to check
     * @return if key exists
     */
    bool imgExits(const std::string& key);

    /**
     * Returns a string
     * @param key key to get
     * @return string
     */
    std::string getString(const std::string& key);

    /**
     * Returns double
     * @param key to get
     * @return double
     */
    double getDouble(const std::string& key);

    /**
     * Returns int
     * @param key key to get
     * @return int
     */
    int getInt(const std::string& key);

    /**
     * Returns bool
     * @param key key to get
     * @return bool
     */
    bool getBool(const std::string &key);

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
    internalJSON_ptr getJSON(const std::string &key);

    /**
     * Sets a img
     * @param key key for the img
     * @param img img to set
     */
    void setImg(const std::string& key, cv::Mat img);

    /**
     * Sets a json value
     * @param key key for the json value
     * @param val value, internalJSON_ptr
     */
    void setJSON(const std::string &key, internalJSON_ptr val);

    /**
     * Prints out a internalJSON_ptr
     * @param json json to print
     */
    static void printJSON(internalJSON_ptr json, int level=0);
};


#endif //ROBOT_GUI_V3_WIDGETDATA_H
