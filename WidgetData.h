#ifndef ROBOT_GUI_V3_WIDGETDATA_H
#define ROBOT_GUI_V3_WIDGETDATA_H
#include <map>
#include "Constants.h"
#include <vector>

class WidgetData {
private:
    std::map<std::string, double> doubleMap;
    std::map<std::string, int> intMap;
    std::map<std::string , std::string> stringMap;
    std::vector<std::vector<std::string>> keyTypes;
public:
    /**
     * Finds the type of data for a given key
     * @param key
     * @return data type <string>
     */
    std::string getKeyType(std::string key);
    /**
     * Saves the key type
     * @param key
     * @param keyType
     */
    void updateKeyType(std::string key, std::string keyType);

    // Getter methods
    std::string getString(std::string key);
    double getDouble(std::string key);
    int getInt(std::string key);

    // Setter methods
    void setString(std::string key, std::string value);
    void setInt(std::string key, int value);
    void setDouble(std::string key, double value);
};


#endif //ROBOT_GUI_V3_WIDGETDATA_H
