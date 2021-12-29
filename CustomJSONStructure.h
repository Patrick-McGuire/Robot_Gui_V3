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
#include "InternalJson.h"


/**
 * These all ended up being fairly similar, so I'm going to base class them all
 */
class BaseCustomJSONStruct {
public:
    BaseCustomJSONStruct(InternalJson::Types type) {
        jsonStruct = InternalJson::create();
        jsonStruct->setType(type);
    }

    InternalJson::SharedPtr getStruct() { return jsonStruct; }

protected:
    InternalJson::SharedPtr jsonStruct;
};

/**
 * Builds a JSON structure for an annunciator widget
 */
class AnnunciatorJSONStruct : public BaseCustomJSONStruct {
public:
    AnnunciatorJSONStruct() : BaseCustomJSONStruct(InternalJson::vector_t) {}

    void addAnnunciator(std::string name, int status, const std::string& description) {
        InternalJson::SharedPtr singleAnnunciator = InternalJson::create();
        singleAnnunciator->setType(InternalJson::vector_t);
        singleAnnunciator->vectorAppend(InternalJson::create(name));
        singleAnnunciator->vectorAppend(InternalJson::create(status));
        singleAnnunciator->vectorAppend(InternalJson::create(name));
//        singleAnnunciator->vector.push_back(WidgetData::getJSONObjectFromString(std::move(name)));
//        singleAnnunciator->vector.push_back(WidgetData::getJSONObjectFromInt(status));
//        singleAnnunciator->vector.push_back(WidgetData::getJSONObjectFromString(std::move(description)));
        jsonStruct->vectorAppend(singleAnnunciator);
//        jsonStruct->vector.push_back(singleAnnunciator);
    }
};

class ConsoleJSONStruct : public BaseCustomJSONStruct {
public:
    ConsoleJSONStruct(int _queueSize) : BaseCustomJSONStruct(InternalJson::vector_t) {
        queueSize = _queueSize;
        jsonStruct->vectorAppend(InternalJson::create(startIndex));
//        jsonStruct->vector.push_back(WidgetData::getJSONObjectFromInt(startIndex));
    }

    void addLog(std::string data, int level) {
        InternalJson::SharedPtr singleLog = InternalJson::create(InternalJson::vector_t);
//        singleLog->type = WidgetData::vector_t;
//        singleLog->vector.push_back(WidgetData::getJSONObjectFromString(data));
//        singleLog->vector.push_back(WidgetData::getJSONObjectFromInt(level));
        singleLog->vectorAppend(InternalJson::create(data));
        singleLog->vectorAppend(InternalJson::create(level));

        if (jsonStruct->vectorSize() < queueSize + 1) {
            jsonStruct->vectorAppend(singleLog);
//            jsonStruct->vector.push_back(singleLog);
        } else {
            startIndex++;
            if (startIndex > jsonStruct->vectorSize() - 1) { startIndex = 1; }
//            jsonStruct->vector[startIndex] = singleLog;
//            jsonStruct->vector[0] = WidgetData::getJSONObjectFromInt(startIndex);
            jsonStruct->vectorSet(startIndex, singleLog);
            jsonStruct->vectorSet(0, InternalJson::create(startIndex));
        }
    }

protected:
    int startIndex = 0;
    int queueSize;
};

#endif //ROBOT_GUI_V3_CUSTOMJSONSTRUCTURE_H
