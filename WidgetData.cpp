#include "WidgetData.h"
#include "iostream"

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





