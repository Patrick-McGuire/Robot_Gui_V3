#include "WidgetData.h"

#include <utility>
#include "iostream"

// Getter methods
std::string WidgetData::getString(const std::string& key) {
    if(jsonMap.count(key)) {
        return jsonMap[key]->stringVal;
    }
    return "";
}
double WidgetData::getDouble(const std::string& key) {
    if(jsonMap.count(key)) {
        return jsonMap[key]->doubleVal;
    }
    return 0;
}
int WidgetData::getInt(const std::string& key) {
    if(jsonMap.count(key)) {
        return jsonMap[key]->intVal;
    }
    return 0;
}
bool WidgetData::getBool(const std::string& key) {
    if(jsonMap.count(key)) {
        return jsonMap[key]->boolVal;
    }
    return false;
}
cv::Mat WidgetData::getImg(const std::string& key) {
    return imgMap[key];
}
WidgetData::internalJSON_ptr WidgetData::getJSON(const std::string &key) {
    if(jsonMap.count(key)) {
        return jsonMap[key];
    }
    return std::make_shared<WidgetData::internalJSON>();
}

void WidgetData::setImg(const std::string& key, cv::Mat img) {
    setKeyUpdated(key, imgType);
    imgMap[key] = std::move(img);
}
void WidgetData::setJSON(const std::string &key, WidgetData::internalJSON_ptr val) {
    setKeyUpdated(key, jsonType);
    jsonMap[key] = val;
}

WidgetData::internalJsonTypes WidgetData::getKeyType(const std::string& key) {
    if(imgMap.count(key)) {
        return img_t;
    }
    if(jsonMap.count(key)) {
        return jsonMap[key]->type;
    }
    return WidgetData::none_t;
}

void WidgetData::setKeyUpdated(const std::string& key, const std::string& keyType) {
    keysUpdated[key] = true;
}

bool WidgetData::imgExits(const std::string& key) {
    return imgMap.count(key);
}

void WidgetData::resetKeysUpdated() {
    for(auto & it : keysUpdated) {
        keysUpdated[it.first] = false;
    }
}

bool WidgetData::keyUpdated(const std::string &key) {
    return keysUpdated[key];
}

void WidgetData::printJSON(WidgetData::internalJSON_ptr json, int level) {
    if(json->type == vector_t) {
        std::cout << "[";
        for(int i = 0; i < json->vector.size(); i++) {
            printJSON(json->vector[i], level + 1);
            if(i != json->vector.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]";
    } else if(json->type == map_t) {
        int j = 0;
        std::cout << "{ ";
        for(auto i = json->map.begin(); i != json->map.end(); ++i, j++) {
            std::cout << i->first << ": ";
            printJSON(i->second, level + 1);
            if(j != json->map.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << " }";
    } else if(json->type == int_t) {
        std::cout << json->intVal;
    } else if(json->type == double_t) {
        std::cout << json->doubleVal;
    } else if(json->type == bool_t) {
        std::cout << (json->boolVal ? "true" : "false");
    } else if(json->type == string_t) {
        std::cout << json->stringVal;
    }
    if(level == 0) {
        std::cout << std::endl;
    }
}





