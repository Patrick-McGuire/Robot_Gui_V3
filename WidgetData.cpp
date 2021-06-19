#include "WidgetData.h"
#include "iostream"

// Getter methods
std::string WidgetData::getString(std::string key) { return stringMap[key]; }
double WidgetData::getDouble(std::string key) {  return doubleMap[key]; }
int WidgetData::getInt(std::string key) { return intMap[key]; }

// Setter methods
void WidgetData::setString(std::string key, std::string value) {
    updateKeyType(key, stringType);
    stringMap[key] = value;
}
void WidgetData::setInt(std::string key, int value) {
    updateKeyType(key, intType);
    intMap[key] = value;
}
void WidgetData::setDouble(std::string key, double value) {
    updateKeyType(key, doubleType);
    doubleMap[key] = value;
}

std::string WidgetData::getKeyType(std::string key) {
    for(auto it = keyTypes.begin(); it != keyTypes.end(); ++it) {
        if(it[0][0] == key) {
            return it[0][1];
        }
    }
    return noType;
}

void WidgetData::updateKeyType(std::string key, std::string keyType) {
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
