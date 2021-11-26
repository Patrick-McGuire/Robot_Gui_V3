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

    struct internalJSON {
        internalJsonTypes type;
        int intVal;
        double doubleVal;
        bool boolVal;
        std::string stringVal;
        std::vector<std::shared_ptr<internalJSON>> vector;
        std::map<std::string, std::shared_ptr<internalJSON>> map;
    };

    typedef std::shared_ptr<internalJSON> internalJSON_ptr;

private:
//    std::map<std::string, double> doubleMap;
//    std::map<std::string, int> intMap;
//    std::map<std::string, bool> boolMap;
//    std::map<std::string , std::string> stringMap;
    std::map<std::string, cv::Mat> imgMap;
    std::map<std::string, internalJSON_ptr> jsonMap;
//    std::vector<std::vector<std::string>> keyTypes;
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

    void resetKeysUpdated();
    bool keyUpdated(const std::string& key);

    bool imgExits(const std::string& key);

    // Getter methods
    std::string getString(const std::string& key);
    double getDouble(const std::string& key);
    int getInt(const std::string& key);
    bool getBool(const std::string &key);
    cv::Mat getImg(const std::string &key);
    internalJSON_ptr getJSON(const std::string &key);

    // Setter methods
//    void setString(const std::string& key, std::string value);
//    void setInt(const std::string& key, int value);
//    void setDouble(const std::string& key, double value);
    void setImg(const std::string& key, cv::Mat img);
//    void setBool(const std::string &key, bool value);
    void setJSON(const std::string &key, internalJSON_ptr val);

    static void printJSON(internalJSON_ptr json, int level=0);
};


#endif //ROBOT_GUI_V3_WIDGETDATA_H
