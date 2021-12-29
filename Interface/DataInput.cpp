#include "DataInput.h"

DataInput::DataInput(WidgetData *_widgetData) {
    widgetData = _widgetData;
    messageSize.length = 0;
}

void DataInput::parse(char *input, int len) {
    auto id = static_cast<RobotGui::MessageType>((int) input[0]);
    for (int i = 0; i < 4; i++) {
        messageSize.bytes[i] = input[i + 1];
    }
    auto returnType = static_cast<RobotGui::ReturnType>((int) input[5]);
    if (messageSize.length <= 0 || messageSize.length + 6 > len) {       // Corrupted/invalid messages are ignored
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
        auto currentKeyType = widgetData->getJsonKeyType(keyName);
        auto json = widgetData->getJSON(keyName);
        parseArray(&doc[keyName.data()], json);
        if (currentKeyType == InternalJson::none_t) {
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
        widgetData->setImg(imgIdStr, cv::imdecode(cv::Mat(1, len + 1, CV_8UC1, input + 1), cv::IMREAD_ANYCOLOR));
    } catch (cv::Exception const &e) {
        // You sent a bad img
        std::cout << "CVERROR\n";
    }
}

void DataInput::parseArray(rapidjson::Value *value, const InternalJson::SharedPtr &json) {
    if (value->IsBool()) {
        json->setBool(value->GetBool());
    } else if (value->IsInt()) {
        json->setInt(value->GetInt());
    } else if (value->IsDouble()) {
        json->setDouble(value->GetDouble());
    } else if (value->IsString()) {
        json->setString(value->GetString());
    } else if (value->IsArray()) {
        json->setType(InternalJson::vector_t);
        auto array = value->GetArray();
        int count = 0;
        for (rapidjson::Value::ConstValueIterator itr = array.Begin(); itr != array.End(); ++itr, count++) {
            InternalJson::SharedPtr eleJson;
            if (count < json->vectorSize()) {
                eleJson = json->vectorGet(count);
            } else {
                eleJson = InternalJson::create();
                json->vectorAppend(eleJson);
            }
            parseArray(&array[count], eleJson);
        }
        while (json->vectorSize() > count) {
            json->vectorPop();
        }
    } else if (value->IsObject()) {
        json->setType(InternalJson::map_t);
        auto obj = value->GetObject();
        rapidjson::Value::MemberIterator M;
        for (M = obj.MemberBegin(); M != obj.MemberEnd(); M++) {
            std::string name = M->name.GetString();
            InternalJson::SharedPtr eleJson;
            if (json->mapCount(name) != 0) {
                eleJson = json->mapGet(name);
            } else {
                eleJson = InternalJson::create();
                json->mapSet(name, eleJson);
            }
            parseArray(&obj[M->name], eleJson);
        }
    }
}
