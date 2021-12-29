#include "InternalJson.h"


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
        } case map_t: {
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
        } case int_t: {
            std::cout << intVal;
            break;
        } case double_t: {
            std::cout << doubleVal;
            break;
        } case bool_t: {
            std::cout << (boolVal ? "true" : "false");
            break;
        } case string_t: {
            std::cout << stringVal;
            break;
        } case none_t: {
            std::cout << " ";
            break;
        }
    }
    if (first) {
        std::cout << std::endl;
    }
}

