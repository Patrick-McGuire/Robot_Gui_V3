#ifndef ROBOT_GUI_V3_INTERNALJSON_H
#define ROBOT_GUI_V3_INTERNALJSON_H

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
 * @class InternalJson
 * Used to store Json data internally with a user friendly interface
 * Thread safe
 *
 * @author Patrick McGuire (Patrick-McGuire)
 */
class InternalJson {
public:
    enum Types {
        int_t,
        double_t,
        bool_t,
        string_t,
        vector_t,
        map_t,
        none_t,
    };
    typedef std::shared_ptr<InternalJson> SharedPtr;

    InternalJson() {
        type = none_t;
    }
    static SharedPtr create() {
        return std::make_shared<InternalJson>();
    }
    explicit InternalJson(int val) {
        type = int_t;
        intVal = val;
    }
    static SharedPtr create(int val) {
        return std::make_shared<InternalJson>(val);
    }
    explicit InternalJson(double val) {
        type = double_t;
        doubleVal = val;
    }
    static SharedPtr create(double val) {
        return std::make_shared<InternalJson>(val);
    }
    explicit InternalJson(bool val) {
        type = bool_t;
        boolVal = val;
    }
    static SharedPtr create(bool val) {
        return std::make_shared<InternalJson>(val);
    }
    explicit InternalJson(const std::string& val) {
        type = string_t;
        stringVal = val;
    }
    static SharedPtr create(const std::string& val) {
        return std::make_shared<InternalJson>(val);
    }

    Types getType() {
        Guard guard(mutex);
        return type;
    }

    void setType(Types _type) {
        Guard guard(mutex);
        type = _type;
    }

    int getInt(int defaultVal=0) {
        Guard guard(mutex);
        return type == int_t ? intVal : defaultVal;
    }

    double getDouble(double defaultVal=0.0) {
        Guard guard(mutex);
        return type == double_t ? doubleVal : defaultVal;
    }

    bool getBool(bool defaultVal=false) {
        Guard guard(mutex);
        return type == bool_t ? boolVal : defaultVal;
    }

    std::string getString(const std::string& defaultVal="") {
        Guard guard(mutex);
        return type == string_t ? stringVal : defaultVal;
    }

    void setInt(int val) {
        Guard guard(mutex);
        type = int_t;
        intVal = val;
    }

    void setDouble(double val) {
        Guard guard(mutex);
        type = double_t;
        doubleVal = val;
    }

    void setBool(bool val) {
        Guard guard(mutex);
        type = bool_t;
        boolVal = val;
    }

    void setString(const std::string& val) {
        Guard guard(mutex);
        type = string_t;
        stringVal = val;
    }

    //// Vector ////
    unsigned long vectorSize() {
        Guard guard(mutex);
        return type == vector_t ? vector.size() : 0;
    }

    void vectorAppend(const SharedPtr& val) {
        Guard guard(mutex);
        vector.push_back(val);
    }

    SharedPtr vectorGet(int index) {
        Guard guard(mutex);
        return vector[index];
    }

    void vectorSet(int index, const SharedPtr& val) {
        Guard guard(mutex);
        vector[index] = val;
    }

    //// Map ////
    unsigned long mapCount(const std::string& key) {
        Guard guard(mutex);
        return map.count(key);
    }

    std::vector<std::string> mapKeys() {
        Guard guard(mutex);
        std::vector<std::string> keys;
        keys.reserve(map.size());
        for(auto & pair : map) {
            keys.push_back(pair.first);
        }
        return keys;
    }

    SharedPtr mapGet(const std::string& key) {
        Guard guard(mutex);
        return map[key];
    }

    void mapSet(const std::string& key, const SharedPtr& val) {
        Guard guard(mutex);
        map[key] = val;
    }

    void print();


private:
    typedef std::lock_guard<std::mutex> Guard;
    typedef std::vector<SharedPtr> JsonVector;
    typedef std::map<std::string, SharedPtr> JsonMap;

    void print(bool first);

    // Tracks what type of JSON object this is
    Types type;
    // JSON Values
    union {                             // Only one of these can be used at a time, so no need to waste memory
        int intVal=0;
        double doubleVal;
        bool boolVal;
    };
    std::string stringVal;
    JsonVector vector;
    JsonMap map;
    // Used for memory management
    std::mutex mutex;
};


#endif //ROBOT_GUI_V3_INTERNALJSON_H
