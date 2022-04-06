#include "DataInput.h"
#include "../src/WidgetData.h"

DataInput::DataInput(RobotGui::WidgetData *_widgetData) {
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
    widgetData->getJson()->parseSuperimpose(input);
    auto keys = widgetData->getJson()->mapKeys();
    for(const auto& key : keys) {
        widgetData->setKeyUpdated(key);
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

