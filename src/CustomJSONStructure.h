/**
 *  Created by nathan on 12/26/21.
 *  Contains classes to build a few custom JSON structures used by specific widgets
 */

#ifndef ROBOT_GUI_V3_CUSTOMJSONSTRUCTURE_H
#define ROBOT_GUI_V3_CUSTOMJSONSTRUCTURE_H

#include <string>
#include <utility>
#include "WidgetData.h"
#include "../lib/CommonFunctions.h"
#include "InternalJson.h"


namespace RobotGui {
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

        void addAnnunciator(std::string name, int status, const std::string &description) {
            InternalJson::SharedPtr singleAnnunciator = InternalJson::create();
            singleAnnunciator->setType(InternalJson::vector_t);
            singleAnnunciator->vectorAppend(InternalJson::create(name));
            singleAnnunciator->vectorAppend(InternalJson::create(status));
            singleAnnunciator->vectorAppend(InternalJson::create(name));
            jsonStruct->vectorAppend(singleAnnunciator);
        }
    };

    class ConsoleJSONStruct : public BaseCustomJSONStruct {
    public:
        ConsoleJSONStruct(int _queueSize) : BaseCustomJSONStruct(InternalJson::vector_t) {
            queueSize = _queueSize;
            jsonStruct->vectorAppend(InternalJson::create(startIndex));
        }

        void addLog(std::string data, int level) {
            InternalJson::SharedPtr singleLog = InternalJson::create(InternalJson::vector_t);
            singleLog->vectorAppend(InternalJson::create(data));
            singleLog->vectorAppend(InternalJson::create(level));

            if (jsonStruct->vectorSize() < queueSize + 1) {
                jsonStruct->vectorAppend(singleLog);
            } else {
                startIndex++;
                if (startIndex > jsonStruct->vectorSize() - 1) { startIndex = 1; }
                jsonStruct->vectorSet(startIndex, singleLog);
                jsonStruct->vectorSet(0, InternalJson::create(startIndex));
            }
        }

    protected:
        int startIndex = 0;
        int queueSize;
    };

    /**
         * {page: [[name, data], [name, data], etc...], page2: [[], [], etc...] etc...}
         */
    class DropDownTextBoxJSONStruct : public BaseCustomJSONStruct {
    public:
        DropDownTextBoxJSONStruct() : BaseCustomJSONStruct(InternalJson::map_t) {}

        /**
         * Adds a line to a given page
         * @param page: Name of page to add to (page will be created if it doesn't exist)
         * @param name: line name
         * @param data: line data
         * @param index: index to set.  If index is -1 this appends, if it is positive it changes an existing line
         */
        void addLine(std::string page, std::string name, std::string data, int index = -1) {
            auto pageData = jsonStruct->mapGetOrAdd(page, InternalJson::vector_t);
            auto line = pageData->vectorGetOrAppend(index, InternalJson::vector_t);
            line->vectorGetOrAppend(0)->setString(name);
            line->vectorGetOrAppend(1)->setString(data);
        }
    };
}

#endif //ROBOT_GUI_V3_CUSTOMJSONSTRUCTURE_H
