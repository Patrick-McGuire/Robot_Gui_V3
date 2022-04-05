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
    std::cout << toString(first) << std::endl;
}

std::string InternalJson::toString(bool first) {
    std::string out_string;

    Guard guard(mutex);
    switch (type) {
        case vector_t: {
            out_string += "[";
            for (int i = 0; i < vector.size(); i++) {
                out_string += vector[i]->toString(false);
                if (i != vector.size() - 1) {
                    out_string += ", ";
                }
            }
            out_string += "]";
            break;
        }
        case map_t: {
            int j = 0;
            out_string += "{ ";
            for (auto i = map.begin(); i != map.end(); ++i, j++) {
                out_string += "\"" + i->first + "\": ";
                out_string += i->second->toString(false);
                if (j != map.size() - 1) {
                    out_string += ", ";
                }
            }
            out_string += " }";
            break;
        }
        case int_t: {
            out_string += std::to_string(intVal);
            break;
        }
        case double_t: {
            out_string += std::to_string(doubleVal);
            break;
        }
        case bool_t: {
            out_string += (boolVal ? "true" : "false");
            break;
        }
        case string_t: {
            out_string += "\"" + stringVal + "\"";
            break;
        }
        case none_t: {
            out_string += " ";
            break;
        }
    }
    if (first) {
        out_string += "\n";
    }

    return out_string;
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
        if (defaultType != none_t) {
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
        if (defaultType != none_t) {
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

InternalJson::SharedPtr InternalJson::create(const char *buf) {
    rapidjson::Document doc;
    doc.Parse(buf);
    return create(&doc);
}

InternalJson::SharedPtr InternalJson::create(rapidjson::Document *doc) {
    SharedPtr rtn = create(map_t);
    for (rapidjson::Value::MemberIterator M = doc->MemberBegin(); M != doc->MemberEnd(); M++) {
        std::string keyName = M->name.GetString();
        SharedPtr json = rtn->mapGetOrAdd(keyName);
        rtn->parseSuperimpose(&M->value, json);
    }
    return rtn;
}

void InternalJson::parseSuperimpose(const char *buf) {
    rapidjson::Document doc;
    doc.Parse(buf);
    parseSuperimpose(&doc);
}

void InternalJson::parseSuperimpose(rapidjson::Document *doc) {
    for (rapidjson::Value::MemberIterator M = doc->MemberBegin(); M != doc->MemberEnd(); M++) {
        std::string keyName = M->name.GetString();
        SharedPtr json = mapGetOrAdd(keyName);
        parseSuperimpose(&M->value, json);
    }
}

void InternalJson::parseSuperimpose(rapidjson::Value *value, const InternalJson::SharedPtr &json) {
    if (value->IsBool()) {
        json->setBool(value->GetBool());
    } else if (value->IsInt()) {
        json->setInt(value->GetInt());
    } else if (value->IsDouble()) {
        json->setDouble(value->GetDouble());
    } else if (value->IsString()) {
        json->setString(value->GetString());
    } else if (value->IsArray()) {
        json->setType(InternalJson::vector_t);
        auto array = value->GetArray();
        int count = 0;
        for (rapidjson::Value::ConstValueIterator itr = array.Begin(); itr != array.End(); ++itr, count++) {
            InternalJson::SharedPtr eleJson;
            if (count < json->vectorSize()) {
                eleJson = json->vectorGet(count);
            } else {
                eleJson = InternalJson::create();
                json->vectorAppend(eleJson);
            }
            parseSuperimpose(&array[count], eleJson);
        }
        while (json->vectorSize() > count) {
            json->vectorPop();
        }
    } else if (value->IsObject()) {
        json->setType(InternalJson::map_t);
        auto obj = value->GetObject();
        rapidjson::Value::MemberIterator M;
        for (M = obj.MemberBegin(); M != obj.MemberEnd(); M++) {
            std::string name = M->name.GetString();
            InternalJson::SharedPtr eleJson;
            if (json->mapCount(name) != 0) {
                eleJson = json->mapGet(name);
            } else {
                eleJson = InternalJson::create();
                json->mapSet(name, eleJson);
            }
            parseSuperimpose(&obj[M->name], eleJson);
        }
    }
}


