/**
 *  Created by nathan on 12/26/21.
 *  Contains classes to build a few custom JSON structures used by specific widgets
 */

#ifndef ROBOT_GUI_V3_CUSTOMJSONSTRUCTURE_H
#define ROBOT_GUI_V3_CUSTOMJSONSTRUCTURE_H

#include <string>
#include <utility>
#include "WidgetData.h"

/**
 * Builds a JSON structure for an annunciator widget
 */
class AnnunciatorJSONStruct {
public:
    AnnunciatorJSONStruct() {
        jsonStruct = std::make_shared<struct WidgetData::internalJSON>();
        jsonStruct->type = WidgetData::vector_t;
    }

    void addAnnunciator(std::string name, int status, std::string description) {
        WidgetData::internalJSON_ptr singleAnnunciator = std::make_shared<struct WidgetData::internalJSON>();
        singleAnnunciator->type = WidgetData::vector_t;
        singleAnnunciator->vector.push_back(WidgetData::getJSONObjectFromString(std::move(name)));
        singleAnnunciator->vector.push_back(WidgetData::getJSONObjectFromInt(status));
        singleAnnunciator->vector.push_back(WidgetData::getJSONObjectFromString(std::move(description)));
        jsonStruct->vector.push_back(singleAnnunciator);
    }

    std::shared_ptr<WidgetData::internalJSON> getStruct() { return jsonStruct; }

protected:
    std::shared_ptr<WidgetData::internalJSON> jsonStruct;
};

#endif //ROBOT_GUI_V3_CUSTOMJSONSTRUCTURE_H
