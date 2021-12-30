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
 * Thread safe, and memory safe (using std::shared_ptr)
 *
 * @author Patrick McGuire (Patrick-McGuire)
 */
class InternalJson {
public:
    /**
     * std::shared_ptr to this object
     */
    typedef std::shared_ptr<InternalJson> SharedPtr;

    /**
     * All possible types that can be stored in InternalJson
     */
    enum Types {
        int_t,
        double_t,
        bool_t,
        string_t,
        vector_t,
        map_t,
        none_t,
    };

    /**
     * Creates a std::shared_ptr to a new InternalJson Object
     * @return std::shared_ptr a new Object
     */
    static SharedPtr create();

    /**
     * Creates a std::shared_ptr to a new InternalJson Object
     * @param _type initial json type
     * @return std::shared_ptr a new Object
     */
    static SharedPtr create(Types _type);

    /**
     * Parses a JSON string into a new InternalJson Object
     * @param buf buffer to parse from
     * @return std::shared_ptr a new Object
     */
    static SharedPtr create(const char *buf);

    /**
     * Turns a rapidjson document into a new InternalJson Object
     * @param doc rapidjson document
     * @return std::shared_ptr a new Object
     */
    static SharedPtr create(rapidjson::Document *doc);

    /**
     * Creates a std::shared_ptr to a new InternalJson Object
     * @param val initial json value
     * @return std::shared_ptr a new Object
     */
    static SharedPtr create(int val);

    /**
     * Creates a std::shared_ptr to a new InternalJson Object
     * @param val initial json value
     * @return std::shared_ptr a new Object
     */
    static SharedPtr create(double val);

    /**
     * Creates a std::shared_ptr to a new InternalJson Object
     * @param val initial json value
     * @return std::shared_ptr a new Object
     */
    static SharedPtr create(bool val);

    /**
     * Creates a std::shared_ptr to a new InternalJson Object
     * @param val initial json value
     * @return std::shared_ptr a new Object
     */
    static SharedPtr create(const std::string &val);

    //// Getters and setters for basic values ////

    /**
     * Gets the type of the this json object
     * @return current type
     */
    Types getType();

    /**
     * Sets the type of this json object
     * @param _type type to set
     */
    void setType(Types _type);

    /**
     * Gets the integer value of this object
     * @param defaultVal value to return if this type is not integer
     * @return integer value
     */
    int getInt(int defaultVal = 0);

    /**
     * Gets the double value of this object
     * @param defaultVal value to return if this type is not double
     * @return double value
     */
    double getDouble(double defaultVal = 0.0);

    /**
     * Gets the boolean value of this object
     * @param defaultVal value to return if this type is not boolean
     * @return boolean value
     */
    bool getBool(bool defaultVal = false);

    /**
     * Gets the string value of this object
     * @param defaultVal value to return if this type is not string
     * @return string value
     */
    std::string getString(const std::string &defaultVal = "");

    /**
     * Sets the integer value for this object
     * @param val value to set
     */
    void setInt(int val);

    /**
     * Sets the double value for this object
     * @param val value to set
     */
    void setDouble(double val);

    /**
     * Sets the boolean value for this object
     * @param val value to set
     */
    void setBool(bool val);

    /**
     * Sets the string value for this object
     * @param val value to set
     */
    void setString(const std::string &val);

    //// Vector ////

    /**
     * Gets the size of the internal vector
     * returns 0 if type is not currently vector_t
     * @return size
     */
    unsigned long vectorSize();

    /**
     * Appends a value to this vector
     * @param val value to append
     */
    void vectorAppend(const SharedPtr &val);

    /**
     * Removes the last element from the vector
     */
    void vectorPop();

    /**
     * Gets a value from the vector object
     * @param index index to retrieve from
     * @return value
     */
    SharedPtr vectorGet(int index);

    /**
     * If index is in range, gets a value from the vector object
     * If out of range, returns a new InternalJson object and appends it to the vector
     * @param index index to retrieve
     * @param defaultType type to make if index is out of range
     * @return value
     */
    SharedPtr vectorGetOrAppend(int index, Types defaultType = none_t);

    /**
     * Sets a value in the vector object
     * @param index index to set
     * @param val value to set
     */
    void vectorSet(int index, const SharedPtr &val);

    //// Map ////

    /**
     * Gets if a key is in the map
     * @param key key to check
     * @return if key exists in map
     */
    unsigned long mapCount(const std::string &key);

    /**
     * Gets a vector<string> containing all keys for the map
     * @return vector of keys
     */
    std::vector<std::string> mapKeys();

    /**
     * Gets a value at a key in the map
     * @param key key to get
     * @return value
     */
    SharedPtr mapGet(const std::string &key);

    /**
     * If key exists, get that value from the map
     * If key doesn't exist, return a new InternalJson object and add it to the map
     * @param key key to get or add
     * @param defaultType type to make if key doesn't exist
     * @return value
     */
    SharedPtr mapGetOrAdd(const std::string &key, Types defaultType = none_t);

    /**
     * Sets a value at a key in the map
     * @param key key to set
     * @param val value to set
     */
    void mapSet(const std::string &key, const SharedPtr &val);

    /**
     * Prints out this object
     */
    void print();

    /**
     * Parses a json string on top of this object
     * Overwrites any values in the buf, but leaves any that aren't
     * @param buf buffer to parse
     */
    void parseSuperimpose(const char *buf);

    /**
     * Parses a rapidjson document on top of this object
     * Overwrites any values in the object, but leaves any that aren't
     * @param doc rapidjson document
     */
    void parseSuperimpose(rapidjson::Document *doc);

private:
    /**
     * Used to lock access to this objects recodes to prevent threading issues
     * Create a instance first thing in every function
     */
    typedef std::lock_guard<std::mutex> Guard;
    /**
     * The internal vector type
     */
    typedef std::vector<SharedPtr> JsonVector;
    /**
     * The internal map type
     */
    typedef std::map<std::string, SharedPtr> JsonMap;

    /**
     * Constructor
     */
    InternalJson();

    /**
     * Constructor
     * @param _type default type
     */
    explicit InternalJson(Types _type);

    /**
     * Constructor
     * @param val default value
     */
    explicit InternalJson(int val);

    /**
     * Constructor
     * @param val default value
     */
    explicit InternalJson(double val);

    /**
     * Constructor
     * @param val default value
     */
    explicit InternalJson(bool val);

    /**
     * Constructor
     * @param val default value
     */
    explicit InternalJson(const std::string &val);

    /**
     * Constructor
     * @param val default value
     */
    void print(bool first);

    /**
     * Recursively parses json values
     * @param value value to parse
     * @param json InternalJson object to parse into
     */
    static void parseSuperimpose(rapidjson::Value *value, const InternalJson::SharedPtr &json);

    // Tracks what type of JSON object this is
    Types type;
    // JSON Values
    union {                             // Only one of these can be used at a time, so no need to waste memory
        int intVal = 0;
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
