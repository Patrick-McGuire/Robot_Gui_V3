#ifndef ROBOT_GUI_V3_WIDGETDATA_H
#define ROBOT_GUI_V3_WIDGETDATA_H

#include <map>
#include "RobotGui.h"
#include <vector>
#include <QtGui/QImage>
#include "opencv2/opencv.hpp"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "thread"
#include "mutex"
#include "Theme.h"
#include "InternalJson.h"

namespace RobotGui {
    /**
         * @class WidgetData
         * Contains all data displayed and output by the widgets
         * Thread safe
         *
         * @author Patrick McGuire (Patrick-McGuire)
         */
    class WidgetData {
    public:
        //// Output ////

        /**
         * Gets the output json object
         * @return output json object
         */
        InternalJson::SharedPtr getOutputJson() {
            std::lock_guard<std::mutex> lockGuard(outJsonMutex);
            return outJson;
        }

        /**
         * Sets a flag high in the output flags
         * @param key key to set high
         */
        void raiseOutputFlag(const std::string &key) {
            std::lock_guard<std::mutex> lockGuard(outFlagsMutex);
            auto element = outFlags->mapGetOrAdd(key, InternalJson::bool_t);
            element->setBool(true);
            //        outFlags[key] = true;
        }

        /**
         * Sets a flag low in the output flags
         * @param key key to set low
         */
        void clearOutputFlag(const std::string &key) {
            std::lock_guard<std::mutex> lockGuard(outFlagsMutex);
            auto element = outFlags->mapGetOrAdd(key, InternalJson::bool_t);
            element->setBool(false);
            //        outFlags[key] = false;
        }

        /**
         * Gets the entire return flags data map
         * @return output flags map
         */
        //    std::map<std::string, bool> *getFlagOutput() {
        InternalJson::SharedPtr getFlagOutput() {
            std::lock_guard<std::mutex> lockGuard(outFlagsMutex);
            return outFlags;
            //        return &outFlags;
        }

        /**
         * Gets a output flag
         * @param key key to get
         * @return flag value
         */
        bool getFlagOutput(const std::string &key) {
            std::lock_guard<std::mutex> lockGuard(outFlagsMutex);
            return outFlags->mapGetOrAdd(key, InternalJson::bool_t)->getBool();
            //        return outFlags.count(key) != 0 && outFlags[key];
        }

        /**
         * Gets if a key exists in the output flags map
         * @param key key to check
         * @return if key exists
         */
        bool outputFlagExists(const std::string &key) {
            std::lock_guard<std::mutex> lockGuard(outFlagsMutex);
            return outFlags->mapCount(key) != 0;
            //        return outFlags.count(key) != 0;
        }

        //// Input ////

        /**
         * Gets the json object
         * @return json object
         */
        InternalJson::SharedPtr getJson() {
            std::lock_guard<std::mutex> lockGuard(jsonMapMutex);
            return jsonMap;
        }


        /**
         * Lowers all updated flags for keys
         */
        void resetKeysUpdated() {
            std::lock_guard<std::mutex> lockGuard(keysUpdatedMutex);
            for (auto &it: keysUpdated) {
                keysUpdated[it.first] = false;
            }
        }

        /**
         * Returns if a key has been updated
         * @param key key to check
         * @return if key has been updated
         */
        bool keyUpdated(const std::string &key) {
            std::lock_guard<std::mutex> lockGuard(keysUpdatedMutex);
            return keysUpdated[key];
        }

        bool keyUpdated() {
            std::lock_guard<std::mutex> lockGuard(keysUpdatedMutex);
            for (auto &it: keysUpdated) {
                if (keysUpdated[it.first]) {
                    return true;
                }
            }
            return false;
        }

        /**
         * Returns if a key corresponds to a img
         * @param key key to check
         * @return if key exists
         */
        bool imgExits(const std::string &key) {
            std::lock_guard<std::mutex> lockGuard(imgMapMutex);
            return imgMap.count(key) != 0;
        }

        /**
         * Returns a img
         * @param key key to get
         * @return img
         */
        cv::Mat getImg(const std::string &key) {
            std::lock_guard<std::mutex> lockGuard(imgMapMutex);
            return imgMap[key];
        }

        QImage getImageAsQImage(const std::string &key) {
            auto img = getImg(key);
            return QImage((uchar *) img.data, img.cols, img.rows, img.step, QImage::Format_ARGB32);
        }

        /**
         * Sets a img
         * @param key key for the img
         * @param img img to set
         */
        void setImg(const std::string &key, cv::Mat img) {
            std::lock_guard<std::mutex> lockGuard(keysUpdatedMutex);
            std::lock_guard<std::mutex> lockGuard2(imgMapMutex);
            keysUpdated[key] = true;
            imgMap[key] = std::move(img);
        }

        /**
         * Saves the key type
         * @param key
         * @param keyType
         */
        void setKeyUpdated(const std::string &key) {
            std::lock_guard<std::mutex> lockGuard(keysUpdatedMutex);
            keysUpdated[key] = true;
        }

        /**
         * Signals to any threads listening to end
         */
        void endGui() {
            std::lock_guard<std::mutex> lockGuard(guiActiveMutex);
            guiActive = false;
        }

        /**
         * Returns if the GUI is active
         * @return if active
         */
        bool getGuiActive() {
            std::lock_guard<std::mutex> lockGuard(guiActiveMutex);
            return guiActive;
        }

    private:
        // Data in storage
        std::mutex imgMapMutex;
        std::mutex jsonMapMutex;
        std::mutex keysUpdatedMutex;
        std::map<std::string, cv::Mat> imgMap;
        InternalJson::SharedPtr jsonMap = InternalJson::create(InternalJson::map_t);;
        std::map<std::string, bool> keysUpdated;
        // Data out storage
        std::mutex outFlagsMutex;
        std::mutex outJsonMutex;
        //    std::map<std::string, bool> outFlags;
        InternalJson::SharedPtr outFlags = InternalJson::create(InternalJson::map_t);
        InternalJson::SharedPtr outJson = InternalJson::create(InternalJson::map_t);
        // Operation
        std::mutex guiActiveMutex;
        bool guiActive = true;
    };
}


#endif //ROBOT_GUI_V3_WIDGETDATA_H
