#include "InternalJson.h"

InternalJson::SharedPtr InternalJson::create() {
    return SharedPtr(new InternalJson());
}

InternalJson::SharedPtr InternalJson::create(InternalJson::Types _type) {
    return SharedPtr(new InternalJson(_type));
}

InternalJson::SharedPtr InternalJson::create(int val) {
    return SharedPtr(new InternalJson(val));
}

InternalJson::SharedPtr InternalJson::create(double val) {
    return SharedPtr(new InternalJson(val));
}

InternalJson::SharedPtr InternalJson::create(bool val) {
    return SharedPtr(new InternalJson(val));
}

InternalJson::SharedPtr InternalJson::create(const std::string &val) {
    return SharedPtr(new InternalJson(val));
}

InternalJson::InternalJson() {
    // Shut up Clang
    doubleVal = 0;
    boolVal = false;
    intVal = 0;
    // ^ Must go first, and really should be removed
    type = none_t;
}

InternalJson::InternalJson(InternalJson::Types _type) {
    // Shut up Clang
    doubleVal = 0;
    boolVal = false;
    intVal = 0;
    // ^ Must go first, and really should be removed
    type = _type;
}

InternalJson::InternalJson(int val) {
    // Shut up Clang
    doubleVal = 0;
    boolVal = false;
    intVal = 0;
    // ^ Must go first, and really should be removed
    type = int_t;
    intVal = val;
}

InternalJson::InternalJson(double val) {
    // Shut up Clang
    doubleVal = 0;
    boolVal = false;
    intVal = 0;
    // ^ Must go first, and really should be removed
    type = double_t;
    doubleVal = val;
}

InternalJson::InternalJson(bool val) {
    // Shut up Clang
    doubleVal = 0;
    boolVal = false;
    intVal = 0;
    // ^ Must go first, and really should be removed
    type = bool_t;
    boolVal = val;
}

InternalJson::InternalJson(const std::string &val) {
    // Shut up Clang
    doubleVal = 0;
    boolVal = false;
    intVal = 0;
    // ^ Must go first, and really should be removed
    type = string_t;
    stringVal = val;
}


void InternalJson::print() {
    print(true);
}

void InternalJson::print(bool first) {
    Guard guard(mutex);
    switch (type) {
        case vector_t: {
            std::cout << "[";
            for (int i = 0; i < vector.size(); i++) {
                vector[i]->print(false);
                if (i != vector.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << "]";
            break;
        }
        case map_t: {
            int j = 0;
            std::cout << "{ ";
            for (auto i = map.begin(); i != map.end(); ++i, j++) {
                std::cout << i->first << ": ";
                i->second->print(false);
                if (j != map.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << " }";
            break;
        }
        case int_t: {
            std::cout << intVal;
            break;
        }
        case double_t: {
            std::cout << doubleVal;
            break;
        }
        case bool_t: {
            std::cout << (boolVal ? "true" : "false");
            break;
        }
        case string_t: {
            std::cout << "\"" << stringVal << "\"";
            break;
        }
        case none_t: {
            std::cout << " ";
            break;
        }
    }
    if (first) {
        std::cout << std::endl;
    }
}

InternalJson::Types InternalJson::getType() {
    Guard guard(mutex);
    return type;
}

void InternalJson::setType(InternalJson::Types _type) {
    Guard guard(mutex);
    type = _type;
}

int InternalJson::getInt(int defaultVal) {
    Guard guard(mutex);
    return type == int_t ? intVal : defaultVal;
}

double InternalJson::getDouble(double defaultVal) {
    Guard guard(mutex);
    return type == double_t ? doubleVal : defaultVal;
}

bool InternalJson::getBool(bool defaultVal) {
    Guard guard(mutex);
    return type == bool_t ? boolVal : defaultVal;
}

std::string InternalJson::getString(const std::string &defaultVal) {
    Guard guard(mutex);
    return type == string_t ? stringVal : defaultVal;
}

void InternalJson::setInt(int val) {
    Guard guard(mutex);
    type = int_t;
    intVal = val;
}

void InternalJson::setDouble(double val) {
    Guard guard(mutex);
    type = double_t;
    doubleVal = val;
}

void InternalJson::setBool(bool val) {
    Guard guard(mutex);
    type = bool_t;
    boolVal = val;
}

void InternalJson::setString(const std::string &val) {
    Guard guard(mutex);
    type = string_t;
    stringVal = val;
}

unsigned long InternalJson::vectorSize() {
    Guard guard(mutex);
    return type == vector_t ? vector.size() : 0;
}

void InternalJson::vectorAppend(const InternalJson::SharedPtr &val) {
    Guard guard(mutex);
    type = vector_t;
    vector.push_back(val);
}

void InternalJson::vectorPop() {
    Guard guard(mutex);
    vector.pop_back();
}


InternalJson::SharedPtr InternalJson::vectorGet(int index) {
    Guard guard(mutex);
    return index < vector.size() && index >= 0 ? vector[index] : create();
}

InternalJson::SharedPtr InternalJson::vectorGetOrAppend(int index, Types defaultType) {
    Guard guard(mutex);
    if (index >= vector.size() || index < 0) {
        SharedPtr newJson = create();
        newJson->setType(defaultType);
        vector.push_back(newJson);
        return newJson;
    } else {
        if(defaultType != none_t) {
            vector[index]->setType(defaultType);
        }
        return vector[index];
    }
}

void InternalJson::vectorSet(int index, const InternalJson::SharedPtr &val) {
    Guard guard(mutex);
    vector[index] = val;
}

unsigned long InternalJson::mapCount(const std::string &key) {
    Guard guard(mutex);
    return map.count(key);
}

std::vector<std::string> InternalJson::mapKeys() {
    Guard guard(mutex);
    std::vector<std::string> keys;
    keys.reserve(map.size());
    for (auto &pair: map) {
        keys.push_back(pair.first);
    }
    return keys;
}

InternalJson::SharedPtr InternalJson::mapGet(const std::string &key) {
    Guard guard(mutex);
    return map.count(key) != 0 ? map[key] : create();
}

InternalJson::SharedPtr InternalJson::mapGetOrAdd(const std::string &key, InternalJson::Types defaultType) {
    Guard guard(mutex);
    if (map.count(key) != 0) {
        if(defaultType != none_t) {
            map[key]->setType(defaultType);
        }
        return map[key];
    } else {
        SharedPtr newJson = create();
        newJson->setType(defaultType);
        map[key] = newJson;
        return newJson;
    }
}

void InternalJson::mapSet(const std::string &key, const InternalJson::SharedPtr &val) {
    Guard guard(mutex);
    map[key] = val;
}

