//
// Created by patrick on 12/2/21.
//

#include "DataInput.h"

DataInput::DataInput(WidgetData *_widgetData, DataInput::DataInputType _type) {
    widgetData = _widgetData;
    type = _type;
    messageSize.length = 0;
}

void DataInput::parse(const char *input, int len) {
    auto id = static_cast<MessageType>((int) input[0]);
    for(int i = 0; i < 4; i++) {
        messageSize.bytes[0] = input[i+1];
    }
    auto returnType = static_cast<ReturnType>((int) input[5]);
    if(messageSize.length <= 0 || messageSize.length + 6 > len) {       // Corrupted/invalid messages are ignored
        return;
    }
    // Remove the first CUSTOM_MSG_HEADER_SIZE elements
    input = &input[CUSTOM_MSG_HEADER_SIZE];
    len - CUSTOM_MSG_HEADER_SIZE;
    // Message type cases
    switch (id) {
        case JSON: {
            parseJson(input, len);
            break;
        }
        case IMG: {
            parseImg(input, len);
            break;
        }
        default: {
            return;
        }
    }
}

void DataInput::parseJson(const char *input, int len) {

}

void DataInput::parseImg(const char *input, int len) {

}
