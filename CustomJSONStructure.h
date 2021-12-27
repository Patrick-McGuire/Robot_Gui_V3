/**
 *  Created by nathan on 12/26/21.
 *  Contains classes to build a few custom JSON structures used by specific widgets
 */

#ifndef ROBOT_GUI_V3_CUSTOMJSONSTRUCTURE_H
#define ROBOT_GUI_V3_CUSTOMJSONSTRUCTURE_H

#include <string>
#include <utility>
#include "WidgetData.h"
#include "CommonFunctions.h"


/**
 * These all ended up being fairly similar, so I'm going to base class them all
 */
class BaseCustomJSONStruct {
public:
    BaseCustomJSONStruct(WidgetData::internalJsonTypes type) {
        jsonStruct = std::make_shared<struct WidgetData::internalJSON>();
        jsonStruct->type = type;
    }

    std::shared_ptr<WidgetData::internalJSON> getStruct() { return jsonStruct; }

protected:
    std::shared_ptr<WidgetData::internalJSON> jsonStruct;
};

/**
 * Builds a JSON structure for an annunciator widget
 */
class AnnunciatorJSONStruct : public BaseCustomJSONStruct {
public:
    AnnunciatorJSONStruct() : BaseCustomJSONStruct(WidgetData::vector_t) {}

    void addAnnunciator(std::string name, int status, std::string description) {
        WidgetData::internalJSON_ptr singleAnnunciator = std::make_shared<struct WidgetData::internalJSON>();
        singleAnnunciator->type = WidgetData::vector_t;
        singleAnnunciator->vector.push_back(WidgetData::getJSONObjectFromString(std::move(name)));
        singleAnnunciator->vector.push_back(WidgetData::getJSONObjectFromInt(status));
        singleAnnunciator->vector.push_back(WidgetData::getJSONObjectFromString(std::move(description)));
        jsonStruct->vector.push_back(singleAnnunciator);
    }
};

class ConsoleJSONStruct : public BaseCustomJSONStruct {
public:
    ConsoleJSONStruct(int _queueSize) : BaseCustomJSONStruct(WidgetData::vector_t) {
        queueSize = _queueSize;
        jsonStruct->vector.push_back(WidgetData::getJSONObjectFromInt(startIndex));
    }

    void addLog(std::string data, int level) {
        WidgetData::internalJSON_ptr singleLog = std::make_shared<struct WidgetData::internalJSON>();
        singleLog->type = WidgetData::vector_t;
        singleLog->vector.push_back(WidgetData::getJSONObjectFromString(data));
        singleLog->vector.push_back(WidgetData::getJSONObjectFromInt(level));

        if (jsonStruct->vector.size() < queueSize + 1) {
            jsonStruct->vector.push_back(singleLog);
        } else {
            startIndex++;
            if (startIndex > jsonStruct->vector.size() - 1) { startIndex = 1; }
            jsonStruct->vector[startIndex] = singleLog;
            jsonStruct->vector[0] = WidgetData::getJSONObjectFromInt(startIndex);
        }
    }

protected:
    int startIndex = 0;
    int queueSize;
};

#endif //ROBOT_GUI_V3_CUSTOMJSONSTRUCTURE_H
