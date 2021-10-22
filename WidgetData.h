#ifndef ROBOT_GUI_V3_WIDGETDATA_H
#define ROBOT_GUI_V3_WIDGETDATA_H
#include <map>
#include "Constants.h"
#include <vector>
#include "opencv2/opencv.hpp"

class WidgetData {
private:
    std::map<std::string, double> doubleMap;
    std::map<std::string, int> intMap;
    std::map<std::string , std::string> stringMap;
    std::map<std::string, cv::Mat> imgMap;
    std::vector<std::vector<std::string>> keyTypes;
public:
    /**
     * Finds the type of data for a given key
     * @param key
     * @return data type <string>
     */
    std::string getKeyType(const std::string& key);
    /**
     * Saves the key type
     * @param key
     * @param keyType
     */
    void updateKeyType(const std::string& key, const std::string& keyType);
    bool imgExits(const std::string& key);

    // Getter methods
    std::string getString(const std::string& key);
    double getDouble(const std::string& key);
    int getInt(const std::string& key);
    cv::Mat getImg(const std::string& key);

    // Setter methods
    void setString(const std::string& key, std::string value);
    void setInt(const std::string& key, int value);
    void setDouble(const std::string& key, double value);
    void setImg(const std::string& key, cv::Mat img);
};


#endif //ROBOT_GUI_V3_WIDGETDATA_H
