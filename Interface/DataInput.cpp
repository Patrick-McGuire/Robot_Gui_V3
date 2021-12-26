//
// Created by patrick on 12/2/21.
//

#include "DataInput.h"

DataInput::DataInput(WidgetData *_widgetData, DataInput::DataInputType _type) {
    widgetData = _widgetData;
    type = _type;
    messageSize.length = 0;
}

void DataInput::parse(char *input, int len) {
    auto id = static_cast<RobotGui::MessageType>((int) input[0]);
    for(int i = 0; i < 4; i++) {
        messageSize.bytes[i] = input[i+1];
    }
    auto returnType = static_cast<RobotGui::ReturnType>((int) input[5]);
    if(messageSize.length <= 0 || messageSize.length + 6 > len) {       // Corrupted/invalid messages are ignored
        return;
    }
    // Remove the first CUSTOM_MSG_HEADER_SIZE elements
    input = &input[CUSTOM_MSG_HEADER_SIZE];
    len = messageSize.length;
    input[messageSize.length] = 0;          // Create a null-terminated string
    // Message type cases
    switch (id) {
        case RobotGui::JSON: {
            parseJson(input, len);
            break;
        }
        case RobotGui::IMG: {
            parseImg(input, len);
            break;
        }
        default: {
            return;
        }
    }
}

void DataInput::parseJson(const char *input, int len) {
    rapidjson::Document doc;
    doc.Parse(input);
    for (rapidjson::Value::MemberIterator M = doc.MemberBegin(); M != doc.MemberEnd(); M++) {
        std::string keyName = M->name.GetString();
        auto currentKeyType = widgetData->getKeyType(keyName);
        auto json = widgetData->getJSON(keyName);
        parseArray(&doc[keyName.data()], json);
        if(currentKeyType == WidgetData::img_t || currentKeyType == WidgetData::none_t) {
            widgetData->setJSON(keyName, json);
        } else {
            widgetData->setKeyUpdated(keyName);
        }
    }
}

void DataInput::parseImg(char *input, int len) {
    uint8_t id = input[0];
    try {
        // Decode the image and save it to widgetData
        auto imgIdStr = std::to_string(id);
        widgetData->setImg(imgIdStr, cv::imdecode(cv::Mat(1, len + 1, CV_8UC1, input+1), cv::IMREAD_ANYCOLOR));
    } catch (cv::Exception const &e) {
        // You sent a bad img
        std::cout << "CVERROR\n";
    }
}

void DataInput::parseArray(rapidjson::Value *value, const WidgetData::internalJSON_ptr& json) {
    if(value->IsBool()) {
        json->boolVal = value->GetBool();
        json->type = WidgetData::bool_t;
    } else if(value->IsInt()) {
        json->intVal = value->GetInt();
        json->type = WidgetData::int_t;
    } else if(value->IsDouble()) {
        json->doubleVal = value->GetDouble();
        json->type = WidgetData::double_t;
    } else if(value->IsString()) {
        json->stringVal = value->GetString();
        json->type = WidgetData::string_t;
    } else if(value->IsArray()) {
        json->type = WidgetData::vector_t;
        auto array = value->GetArray();
        int count = 0;
        for (rapidjson::Value::ConstValueIterator itr = array.Begin(); itr != array.End(); ++itr, count++) {
            WidgetData::internalJSON_ptr eleJson;
            if(count < json->vector.size()) {
                eleJson = json->vector[count];
            } else {
                eleJson = std::make_shared<WidgetData::internalJSON>();
                json->vector.push_back(eleJson);
            }
            parseArray(&array[count], eleJson);
        }
        while (json->vector.size() > count) {
            json->vector.pop_back();
        }
    } else if(value->IsObject()) {
        json->type = WidgetData::map_t;
        auto obj = value->GetObject();
        rapidjson::Value::MemberIterator M;
        for (M = obj.MemberBegin(); M != obj.MemberEnd(); M++) {
            std::string name = M->name.GetString();
            WidgetData::internalJSON_ptr eleJson;
            if(json->map.count(name) != 0) {
                eleJson = json->map[name];
            } else {
                eleJson = std::make_shared<WidgetData::internalJSON>();
                json->map[name] = eleJson;
            }
            parseArray(&obj[M->name], eleJson);
        }
    }
}
