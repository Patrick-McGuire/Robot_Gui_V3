#include "WidgetData.h"

#include <utility>
#include "iostream"

// Getter methods
std::string WidgetData::getString(const std::string& key) { return stringMap[key]; }
double WidgetData::getDouble(const std::string& key) {  return doubleMap[key]; }
int WidgetData::getInt(const std::string& key) { return intMap[key]; }
bool WidgetData::getBool(const std::string& key) { return boolMap[key]; }
cv::Mat WidgetData::getImg(const std::string& key) { return imgMap[key]; }

// Setter methods
void WidgetData::setString(const std::string& key, std::string value) {
    updateKeyType(key, stringType);
    stringMap[key] = std::move(value);
}
void WidgetData::setInt(const std::string& key, int value) {
    updateKeyType(key, intType);
    intMap[key] = value;
}
void WidgetData::setDouble(const std::string& key, double value) {
    updateKeyType(key, doubleType);
    doubleMap[key] = value;
}
void WidgetData::setBool(const std::string& key, bool value) {
    updateKeyType(key, boolType);
    boolMap[key] = value;
}
void WidgetData::setImg(const std::string& key, cv::Mat img) {
    updateKeyType(key, imgType);
    imgMap[key] = img;
}

std::string WidgetData::getKeyType(const std::string& key) {
    for(auto it = keyTypes.begin(); it != keyTypes.end(); ++it) {
        if(it[0][0] == key) {
            return it[0][1];
        }
    }
    return noType;
}

void WidgetData::updateKeyType(const std::string& key, const std::string& keyType) {
    for(auto it = keyTypes.begin(); it != keyTypes.end(); ++it) {
        if(it[0][0] == key) {
            it[0][1] = keyType;
            return;
        }
    }
    std::vector<std::string> test;
    test.push_back(key);
    test.push_back(keyType);
    keyTypes.push_back(test);
}

bool WidgetData::imgExits(const std::string& key) {
    return imgMap.count(key) > 0;
}

